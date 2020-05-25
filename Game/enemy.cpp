#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string id)
	: Game_Object(id, "Texture.Enemy.Walk.Down")
{
	_speed = 0.15f;
	_hp = 3;
	_attackSpeed = 20.f;
	_range = 350;

	_width = 150;
	_height = 150;

	_translation = Vector_2D(500, 500);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::walking);
}

Enemy::~Enemy()
{
}

void Enemy::simulate_AI(Uint32, Assets* assets, Input* input, Scene* scene)
{
	Game_Object* player = scene->get_game_object("Player"); // get player object
	Vector_2D playerTranslation = player->translation(); //get player objects position
	Vector_2D directionToPlayer = (playerTranslation - _translation); //get direction to player
	directionToPlayer.normalize(); //normalize position
	_velocity += directionToPlayer; //move towards the player
	_velocity.scale(_speed); //at the scale of the speed


	bool isWalking = true;
	bool isAgro = false;
	bool isDead = false;
	
	Vector_2D distanceToPlayer = (_translation - playerTranslation); //get distance to player
	if (distanceToPlayer.magnitude() < _range) //if its less then the agro range
	{
		isAgro = true; //set agro to true
		isWalking = false; //set walking to false
	} 
	else 
	{
		isWalking = true; //set walking to true
		isAgro = false; //set agro to false
	}

	if (distanceToPlayer.magnitude() < ((_collider.radius() * 2) + 5))
	{
		player->set_hp(player->hp() - 1); //subtract from player hp
	}

	switch (_state.top())
	{
	case State::walking: //while state is idle
		if (isAgro)
		{
			push_state(State::agro, assets, input);
		}
		if (isDead)
		{
			push_state(State::dead, assets, input);
		}
		break;
	case State::agro: //while state is walking
		if (isWalking)
		{
			pop_state(assets, input);
		} 
		if (isDead)
		{
			push_state(State::dead, assets, input);
		}
		break;
	case State::dead: //while state shooting
		break;
	}
}

void Enemy::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
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

void Enemy::handle_enter_state(State state, Assets*, Input*)
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
	case State::dead:
		//texture = dead
		break;
	}
}

void Enemy::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::walking:
		break;
	case State::agro:
		break;
	case State::dead:
		//give coins or someting
		break;
	}
}
