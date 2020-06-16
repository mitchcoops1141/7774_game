#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string id, Vector_2D translation)
	: Game_Object(id, "Texture.Enemy.Walk.Down")
{
	_speed = 0.15f;
	_hp = 30;
	_attackSpeed = 20;
	_range = 500;
	_knockback = 2;

	_isDead = false;
	_isWalking = true;
	_isAgro = false;

	_width = 200;
	_height = 200;

	_translation = translation;

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::walking);
<<<<<<< HEAD
	
	
	_frame_count = 4;
	_frame_duration_milliseconds = 150;

	int rand_num = rand() % 500;

	_walkingTextureID = "Texture.Enemy.Walk.Down." + std::to_string(time(NULL)) + std::to_string(rand_num);
	//the texture id must include time so string is always diferent. when created at the same time though, the random number on the end diferentiates enemies.
	_texture_id = _walkingTextureID; //set the texture id

	//create enemy walk down texture
	{
		Animated_Texture* texture = new Animated_Texture(
			_walkingTextureID,
			"Assets/enemy.walk.down.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			true);
		assets->add_animated_asset(texture);
	}
	
	_frame_duration_milliseconds = 100;
	_agroTextureID = "Texture.Enemy.Agro.Down." + std::to_string(time(NULL)) + std::to_string(rand_num);

	//create agro texture
	{
		Animated_Texture* texture = new Animated_Texture(
			_agroTextureID,
			"Assets/enemy.agro.down.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			true);
		assets->add_animated_asset(texture);
	}

	_frame_count = 14;
	_deadTextureID = "Texture.Enemy.Death." + std::to_string(time(NULL)) + std::to_string(rand_num);
	{
		Animated_Texture* texture = new Animated_Texture(
			_deadTextureID,
			"Assets/enemy.death.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			false);
		assets->add_animated_asset(texture);
	}
	
=======
>>>>>>> parent of 4fd5077... ENEMIES HAVE INDIVIDUAL ANIMATIONS!
}

Enemy::~Enemy()
{
}

void Enemy::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer*)
{
	//contain the player in the world boundaries
	if (_translation.x() < 125)
	{
		_translation = Vector_2D(125, _translation.y());
	}

	if (_translation.x() > 3535)
	{
		_translation = Vector_2D(3535, _translation.y());
	}

	if (_translation.y() < 50)
	{
		_translation = Vector_2D(_translation.x(), 50);
	}

	if (_translation.y() > 1750)
	{
		_translation = Vector_2D(_translation.x(), 1750);
	}

	Game_Object* player = scene->get_game_object("Player"); // get player object
	if (!player)
	{
		return;
	}
	Vector_2D playerTranslation = player->translation(); //get player objects position
	Vector_2D directionToPlayer = (playerTranslation - _translation); //get direction to player
	directionToPlayer.normalize(); //normalize position
	_velocity += directionToPlayer; //move towards the player
	_velocity.scale(_speed); //at the scale of the speed

	//state variables
	bool isHurt = false;
	
	if (!_isDead) //run all this code if not dead
	{
		Vector_2D distanceToPlayer = (_translation - playerTranslation); //get distance to player
		if (distanceToPlayer.magnitude() < _range) //if its less then the agro range
		{
			_isAgro = true; //set agro to true
			_isWalking = false; //set walking to false
		}
		else
		{
			_isWalking = true; //set walking to true
			_isAgro = false; //set agro to false
		}

		if (distanceToPlayer.magnitude() < ((_collider.radius() * 2) + 5)) //if the player is in contact range ot enemy
		{
			player->set_hp(player->hp() - 1); //subtract from player hp
		}

		std::vector<Game_Object*> game_objects = scene->get_game_objects(); //get all game objects

		for (Game_Object* game_object : game_objects) //loop through game objects
		{
			if (game_object->id().substr(0, 4) == "Ball") //if the first 4 letters of object id are "Ball"
			{
				Vector_2D centerOfEnemy(_translation.x() + _width / 2, _translation.y() + _height / 2); //get center of enemy
				Vector_2D distanceToBall = (centerOfEnemy - game_object->translation()); //get distance to ball

				if ((distanceToBall.magnitude() > 0) && (distanceToBall.magnitude() < ((_collider.radius() * 2)))) //if that distance is less than diameter of collider
				{
					this->set_hp(_hp - player->attackDamage()); //run set hp function
					isHurt = true; //set state to hurt

					//hit sound effect
					Sound* sound = (Sound*)assets->get_asset("Sound.Paper.Hitting");
					Mix_PlayChannel(2, sound->data(), 0);
					Mix_Volume(2, MIX_MAX_VOLUME / 2);

					_velocity += game_object->velocity(); //set velocity to balls velocity
					_velocity.scale(_knockback); //scale it to the knockback

					
					
					game_object->set_to_be_destroyed(true);
				}
			}


		}
	}

	switch (_state.top())
	{
	case State::walking: //while state is idle
		if (_isAgro)
		{
			push_state(State::agro, assets, input);
		}
		if (_isDead)
		{
			push_state(State::dead, assets, input);
		}
		if (isHurt)
		{
			push_state(State::hurt, assets, input);
		}
		break;
	case State::agro: //while state is agro
		if (_isWalking)
		{
			pop_state(assets, input);
		} 
		if (_isDead)
		{
			push_state(State::dead, assets, input);
		}
		if (isHurt)
		{
			push_state(State::hurt, assets, input);
		}
		break;
	case State::hurt: //while state is hurt
	{
		_hurtColorTimer_ms -= milliseconds_to_simulate;
		if (_hurtColorTimer_ms < int(milliseconds_to_simulate))
		{
			pop_state(assets, input);
		}
		break;
	}
	case State::dead: //while state dead
		_deathAnimationTimer_ms -= milliseconds_to_simulate;
		if (_deathAnimationTimer_ms < milliseconds_to_simulate * 2)
		{
			_to_be_destroyed = true;
		}
		break;
	}
}

void Enemy::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);
	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);	
}

void Enemy::set_hp(int hp)
{
	_hp = hp; //set hp

	if (_hp <= 0)
	{
		_isDead = true;
	}
}

void Enemy::push_state(State state, Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, input);
}

void Enemy::pop_state(Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, input);
}

void Enemy::handle_enter_state(State state, Assets* assets, Input*)
{
	
	switch (state)
	{
	case State::walking:
		//texture = wlaking down
		_texture_id = "Texture.Enemy.Walk.Down";
		_speed = 0.15f;
		break;
	case State::agro:
		//texture = agro down
		_texture_id = "Texture.Enemy.Agro.Down";
		_speed = 0.25f;
		break;
	case State::hurt:
	{
		Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
		_hurtColorTimer_ms = 250;
		SDL_SetTextureColorMod(texture->data(), 255, 0, 0);
		break;
	}
	case State::dead:
		//texture = dead
		_deathAnimationTimer_ms = 100 * 14;
		_texture_id = _deadTextureID;
		_speed = 0.f;
		Sound* sound = (Sound*)assets->get_asset("Sound.Enemy.Death"); //get death sound
		Mix_PlayChannel(3, sound->data(), 0); //paly sound
		Mix_Volume(3, MIX_MAX_VOLUME / 3); //lower volume
		
		break;
	}
}

void Enemy::handle_exit_state(State state, Assets* assets)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	switch (state)
	{
	case State::walking:
		break;
	case State::agro:
		break;
	case State::hurt:
		SDL_SetTextureColorMod(texture->data(), 255, 255, 255);
		break;
	case State::dead:
		//give coins or someting
		break;
	}
}
