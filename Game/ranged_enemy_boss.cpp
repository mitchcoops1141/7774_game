#include "ranged_enemy.h"
#include "Spit_ball.h"
#include <iostream>
#include <time.h>
#include "ranged_enemy_boss.h"
#include "spit_ball_boss.h"


Ranged_Enemy_Boss::Ranged_Enemy_Boss(std::string id, Vector_2D translation, Assets* assets, SDL_Renderer* renderer)
	: Game_Object(id, _walkingTextureID)
{
	_speed = 0.25f;
	_hp = 150;
	_attackSpeed = 100;
	_range = 850;
	_knockback = 1.25f;

	_isDead = false;
	_isWalking = true;
	_isShooting = false;

	_width = 325;
	_height = 325;

	_translation = translation;

	_collider.set_radius(_width / 7.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::walking);


	_frame_count = 4;
	_frame_duration_milliseconds = 150;


	int rand_num = rand() % 500;

	_walkingTextureID = "Texture.Ranged.Enemy.Walk.Down." + std::to_string(time(NULL)) + std::to_string(rand_num);
	_texture_id = _walkingTextureID; //i need this code otherwise error. dont ask why...

	//create enemy walk down texture
	{
		Animated_Texture* texture = new Animated_Texture(
			_walkingTextureID,
			"Assets/ranged.enemy.walk.down.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			true);
		assets->add_animated_asset(texture);
	}

	_frame_duration_milliseconds = 150;
	_shootingTextureID = "Texture.Ranged.Enemy.Attack.Down." + std::to_string(time(NULL)) + std::to_string(rand_num);

	//create shooting texture
	{
		Animated_Texture* texture = new Animated_Texture(
			_shootingTextureID,
			"Assets/ranged.enemy.attack.down.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			true);
		assets->add_animated_asset(texture);
	}

	_frame_count = 13;
	_frame_duration_milliseconds = 100;
	_deadTextureID = "Texture.Ranged.Enemy.Death." + std::to_string(time(NULL)) + std::to_string(rand_num);
	{
		Animated_Texture* texture = new Animated_Texture(
			_deadTextureID,
			"Assets/ranged.enemy.death.png",
			renderer,
			_frame_count,
			_frame_duration_milliseconds,
			false);
		assets->add_animated_asset(texture);
	}
}

Ranged_Enemy_Boss::~Ranged_Enemy_Boss()
{
}

void Ranged_Enemy_Boss::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer*)
{
	//contain the enemy in the world boundaries
	if (_translation.x() < 125)
	{
		_translation = Vector_2D(125, _translation.y());
	}

	if (_translation.x() > 3400)
	{
		_translation = Vector_2D(3400, _translation.y());
	}

	if (_translation.y() < 75)
	{
		_translation = Vector_2D(_translation.x(), 75);
	}

	if (_translation.y() > 1600)
	{
		_translation = Vector_2D(_translation.x(), 1600);
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

	//_shoot_cooldown -= milliseconds_to_simulate;

	if (!_isDead) //run all this code if not dead
	{
		Vector_2D distanceToPlayer = (_translation - playerTranslation); //get distance to player
		if (distanceToPlayer.magnitude() < _range) //if its less then the agro range
		{
			_isShooting = true; //set agro to true
			_isWalking = false; //set walking to false

		}
		else
		{
			_isWalking = true; //sets walking to true
			_isShooting = false; //set agro to false
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
		if (_isShooting)
		{
			push_state(State::shooting, assets, input);
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
	case State::shooting: //while state is agro
		_time_to_pop_ms -= milliseconds_to_simulate;
		if (_time_to_pop_ms <= int(milliseconds_to_simulate))
		{
			//create spit ball!
			scene->add_game_object(new Spit_Ball_Boss(_ballID, scene, Vector_2D(_translation.x() + _width / 2, _translation.y() + _height / 2))); //add projectile object
			_ballCounter++; //add one to the ball counter
			_ballID = "SpitBallBoss"; //reset the ball id
			_ballID.append(std::to_string(_ballCounter)); //append the counter to the id to create "ball#"
			pop_state(assets, input);
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

void Ranged_Enemy_Boss::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);
	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Ranged_Enemy_Boss::set_hp(int hp)
{
	_hp = hp; //set hp

	if (_hp <= 0)
	{
		_isDead = true;
	}
}

void Ranged_Enemy_Boss::push_state(State state, Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, input);
}

void Ranged_Enemy_Boss::pop_state(Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, input);
}

void Ranged_Enemy_Boss::handle_enter_state(State state, Assets* assets, Input*)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	switch (state)
	{
	case State::walking:
		//texture = wlaking down
		_texture_id = _walkingTextureID;
		_speed = 0.15f;
		break;
	case State::shooting:
	{
		//texture = agro down
		_texture_id = _shootingTextureID;
		_speed = 0.f;
		_time_to_pop_ms = 400;
		break;
	}
	case State::hurt:
	{
		_hurtColorTimer_ms = 250;
		SDL_SetTextureColorMod(texture->data(), 255, 0, 0);
		break;
	}
	case State::dead:
	{
		//texture = dead
		_deathAnimationTimer_ms = 100 * 13;
		_texture_id = _deadTextureID;
		_speed = 0.f;
		Sound* sound = (Sound*)assets->get_asset("Sound.Ranged.Enemy.Death"); //get death sound
		Mix_PlayChannel(3, sound->data(), 0); //paly sound
		Mix_Volume(3, MIX_MAX_VOLUME / 2); //lower volume
		break;
	}
	}
}

void Ranged_Enemy_Boss::handle_exit_state(State state, Assets* assets)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	switch (state)
	{
	case State::walking:
		break;
	case State::shooting:
	{
		//shoot sound effect
		Sound* sound = (Sound*)assets->get_asset("Sound.Ranged.Enemy.Shoot");
		Mix_PlayChannel(2, sound->data(), 0);
		Mix_Volume(2, MIX_MAX_VOLUME / 2);
		break;
	}
	case State::hurt:
		SDL_SetTextureColorMod(texture->data(), 255, 255, 255);
		break;
	case State::dead:
		//give coins or someting
		break;
	}
}
