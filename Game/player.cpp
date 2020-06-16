#pragma once

#include "player.h"
#include "player_body.h"
#include "player_legs.h"
#include "paper_ball.h"
#include <iostream>
#include "enemy.h"
#include "text.h"
#include "hud.h"


Player::Player(std::string id)
	: Game_Object(id, "Texture.Player.Blank"), _generator((int)time(NULL))
{
	_speed = 50.f; //DEFAULT = 50. MAX = 100. MIN = 10
	_hp = 5; //starts at 5?
	_attackSpeed = 25; //DEFAULT = 25. MAX = infinte. MIN = 5
	_projectileSpeed = 50.f; //DEFAULT = 50. MAX = 75. MIN = 10
	_range = 50; //DEFAULT = 50. MAX = infinite. MIN = 10
	_attackDamage = 10; //DEFAULT = 10. MAX = infinte. Min = 1

	_width = 175;
	_height = 175;

	_translation = Vector_2D(200, 100);

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::Alive);

	_shouldCreateHUD = false;
	_start = true;
}
Player::~Player()
{
}

void Player::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer)
{	
	if (_shouldCreateHUD) //check if should create HUD
	{
		scene->add_game_object(new HUD("HUD", renderer, scene)); //add hud
		_shouldCreateHUD = false; //set create hud to false
	}

	//lock attirbutes to there ranges
	if (_speed < 10)
	{
		_speed = 10;
	}
	if (_speed > 100)
	{
		_speed = 100;
	}
	if (_attackSpeed < 5)
	{
		_attackSpeed = 5;
	}
	if (_projectileSpeed < 10)
	{
		_projectileSpeed = 10;
	}
	if (_projectileSpeed > 75)
	{
		_projectileSpeed = 75;
	}
	if (_range < 10)
	{
		_range = 10;
	}
	if (_attackDamage < 1)
	{
		_attackDamage = 1;
	}
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	if (_attackSpeed < 5)
	{
		_attackSpeed = 5;
	}
	_velocity = Vector_2D(0, 0);

	//movement input
	if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0.5f, 0);
	}

	if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-0.5f, 0);
	}

	if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -0.5f);
	}

	if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 0.5f);
	}

	_velocity.normalize();
	_velocity.scale(_speed / 100);
	
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

	if (_translation.y() > 1800)
	{
		_translation = Vector_2D(_translation.x(), 1800);
	}

	bool isDead = false;

	if (_hp <= 0)
	{
		isDead = true;
	}

	switch (_state.top())
	{
	case State::Alive: //while state is idle

		if (_isHurt)
		{
			push_state(State::Hurt, assets, input);
		}
		if (isDead)
		{
			push_state(State::Dead, assets, input);
		}
		break;
	case State::Hurt: //while state is in hurt state
	{
		//create and render texts
		Game_Object* hud = scene->get_game_object("HUD"); //get the hud object
		hud->set_to_be_destroyed(true); //destroy hud at end of frame
		_shouldCreateHUD = true; //set should create hud to true

		_invincibilityCooldown_ms -= milliseconds_to_simulate;

		if (_invincibilityCooldown_ms < 0)
		{
			pop_state(assets, input);
		}
		break;
	}
	case State::Dead:
		_speed = 0.f;
		Game_Object* playerBody = scene->get_game_object("Player.Body");
		playerBody->set_texture_id("Texture.Player.Blank");
		if (!playerBody)
		{
			return;
		}
		Game_Object* playerLegs = scene->get_game_object("Player.Legs");
		playerLegs->set_texture_id("Texture.Player.Blank");
		if (!playerLegs)
		{
			return;
		}

		//scene->remove_game_object("Player.Body");
		//scene->remove_game_object("Player.Legs");

		Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id); //get texture
		if (texture->get_current_frame() == texture->get_frame_count() - 1) //check if death animation has finished
		{
			//scene->get_game_object("Player.Body")->set_to_be_destroyed(true);
			//scene->get_game_object("Player.Legs")->set_to_be_destroyed(true);
			_to_be_destroyed = true;
		}
		break;
	}

}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	if (_start)
	{
		if (config->hardMode)
		{
			_hp = 3;
			_start = false;
		}
		else
		{
			_hp = 5;
			_start = false;
		}
	}
	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Player::set_hp(int hp)
{
	if (!_isHurt)
	{
		_hp = hp;
		_isHurt = true;
	}
}

void Player::push_state(State state, Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, input);
}

void Player::pop_state(Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, input);
}

void Player::handle_enter_state(State state, Assets* assets, Input*)
{
	switch (state)
	{
	case State::Alive:
		break;
	case State::Hurt:
	{
		_invincibilityCooldown_ms = 750.f; //set invicibility cooldown

		_texture_id = "Texture.Shield"; //set texture to the shield texture

		float hurt_sound_choice = ((float)_generator() / _generator.max()) * 5; //get random number between 1 and 5

		//play hurt sounds
		const int hurt_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Player.Hurt." + std::to_string((int)hurt_sound_choice + 1)); //get sound depending on random number
		Mix_PlayChannel(hurt_channel, sound->data(), 0);
		if ((int)round(hurt_sound_choice + 1) == 2) //if = 2
		{
			Mix_Volume(hurt_channel, MIX_MAX_VOLUME / 3); //lower volume
		}
		else if ((int)round(hurt_sound_choice + 1) > 2) //if = 3,4,5
		{
			Mix_Volume(hurt_channel, MIX_MAX_VOLUME); //set volume to max
		}
	
		break;
	}
	case State::Dead:
		_texture_id = "Texture.Player.Death";
		break;
	}
}

void Player::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::Alive:
		break;
	case State::Hurt:	
		_texture_id = "Texture.Player.Blank";
		_isHurt = false;
		break;
	case State::Dead:
		break;
	}
}