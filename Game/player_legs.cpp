#include "player_legs.h"
#include <iostream>

Player_Legs::Player_Legs(std::string id)
	: Game_Object(id, "Texture.Player.Legs.Idle")
{
	_translation = Vector_2D(50, 50);

	_state.push(State::Idle);

	_width = 150;
	_height = 150;
}

Player_Legs::~Player_Legs()
{
}


void Player_Legs::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Player_Legs::simulate_AI(Uint32, Assets* assets, Input* input, Scene* scene, SDL_Renderer*)
{



	Game_Object* player = scene->get_game_object("Player");
	_translation = player->translation();
	
	//check if walking
	if ((input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN)) ||
		(input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN)) ||
		(input->is_button_state(Input::Button::UP, Input::Button_State::DOWN)) ||
		(input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN)))
	{
		_isWalking = true;
	}
	else //if W,A,S,D not input
	{
		_isWalking = false; //player is not walking
	};

	switch (_state.top())
	{
	case State::Idle: //if idle
		//chcek if walking. state = walking
		if (_isWalking)
		{
			push_state(State::Walking, assets);
		}
		break;
	case State::Walking: //if walking
		if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
		{
			//walking left
			_texture_id = "Texture.Player.Legs.Walk.Left";
		}
		else if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
		{
			//walking right
			_texture_id = "Texture.Player.Legs.Walk.Right";
		}
		else if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
		{
			//walking up
			_texture_id = "Texture.Player.Legs.Walk.Up";
		}
		else if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
		{
			//walking down
			_texture_id = "Texture.Player.Legs.Walk.Down";
		}

		//check if not walking, state pop
		if (!_isWalking)
		{
			push_state(State::Idle, assets);
		}
		break;
	}
}

void Player_Legs::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}

void Player_Legs::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player_Legs::handle_enter_state(State state, Assets* assets)
{
	switch (state)
	{
	case State::Idle:
		//set texture to idle
		_texture_id = "Texture.Player.Legs.Idle";
		break;
	case State::Walking:
	{
		//play walking sounds
		const int walking_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Player.Walking");
		Mix_PlayChannel(walking_channel, sound->data(), -1);
		Mix_Volume(walking_channel, MIX_MAX_VOLUME / 2);
		break;
	}
	}
}

void Player_Legs::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::Idle:
		break;
	case State::Walking:
	{
		//stop walking sounds
		const int walking_channel = 1;
		Mix_HaltChannel(walking_channel);
		break;
	}
	}
}