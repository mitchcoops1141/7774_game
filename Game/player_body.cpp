#include "player_body.h"
#include "paper_ball.h"
#include <iostream>
#include <string>

Player_Body::Player_Body(std::string id)
	: Game_Object(id, "Texture.Player.Body.Idle")
{
	_translation = Vector_2D(50, 50);
	_state.push(State::Idle);

	_width = 150;
	_height = 150;

}

Player_Body::~Player_Body()
{
}

void Player_Body::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Player_Body::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer*)
{
	Game_Object* player = scene->get_game_object("Player"); //get the palyer object

	_translation = player->translation(); //set translation of the body to the translation of the player

	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id); //get the texture of the player body
	texture->set_frame_duration_milliseconds(int(player->attackSpeed() * 6)); //set frame length for texture
	
	_shoot_cooldown_ms -= milliseconds_to_simulate; //minus from the cooldown

	//check if walking
	if ((input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))  ||
		(input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN)) ||
		(input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))	  ||
		(input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN)))
	{
		_isWalking = true;
	}
	else //if W,A,S,D not input
	{
		_isWalking = false; //player is not walking
	};

	//check if shooting
	if ((input->is_button_state(Input::Button::SHOOTING_RIGHT, Input::Button_State::DOWN)) //if shooting right
	|| (input->is_button_state(Input::Button::SHOOTING_LEFT, Input::Button_State::DOWN)) //if shooting left
	|| (input->is_button_state(Input::Button::SHOOTING_DOWN, Input::Button_State::DOWN)) //if shooting down
	|| (input->is_button_state(Input::Button::SHOOTING_UP, Input::Button_State::DOWN))) //if shooting up
	{
		//check if cooldown is finished
		if (_shoot_cooldown_ms < int(milliseconds_to_simulate))
		{
			_isShooting = true; //set shooting variable to true
			_shoot_cooldown_ms = texture->get_frame_duration_milliseconds(); //reset the cooldown
		}
	}
	else {
		_isShooting = false; //set shooting variable to false
	}

	switch (_state.top())
	{
	case State::Idle: //while state is idle
		if (_isWalking) //if player is walking
		{
			push_state(State::Walking, assets, input); //set state walking
		}
		if (_isShooting) //if player is shooting
		{
			push_state(State::Shooting, assets, input); //set state shooting
		}
		break;
	case State::Walking: //while state is walking
		if (input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
		{
			_texture_id = "Texture.Player.Body.Walk.Up";
		}
		else if (input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
		{
			_texture_id = "Texture.Player.Body.Walk.Down";
		}
		else if (input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
		{
			_texture_id = "Texture.Player.Body.Walk.Left";
		}
		else if (input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
		{
			_texture_id = "Texture.Player.Body.Walk.Right";
		}
		if (!_isWalking) //if not walking
		{
			pop_state(assets, input); //pop state
		}
		if (_isShooting) //if shooting
		{
			push_state(State::Shooting, assets, input); //set state shooting
		}
		break;
	case State::Shooting: //while state shooting
		{
			_time_to_pop_ms -= milliseconds_to_simulate;
			if (_time_to_pop_ms < int(milliseconds_to_simulate))
			{
				scene->add_game_object(new Paper_Ball(_ballID, scene, _shootDirection)); //add projectile object
				_ballCounter++; //add one to the ball counter
				_ballID = "Ball"; //reset the ball id
				_ballID.append(std::to_string(_ballCounter)); //append the counter to the id to create "ball#"
				pop_state(assets, input);
			}
		}
		break;
	}
}

void Player_Body::push_state(State state, Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, input);
}

void Player_Body::pop_state(Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, input);
}

void Player_Body::handle_enter_state(State state, Assets* assets, Input* input)
{
	

	switch (state)
	{
	case State::Idle:
		//set texture to idle
			_texture_id = "Texture.Player.Body.Idle";
		break;
	case State::Walking:
		break;
	case State::Shooting:
	{
		{
			//get input direction of shooting and set texture to determined direction
			if (input->is_button_state(Input::Button::SHOOTING_RIGHT, Input::Button_State::DOWN))
			{
				_texture_id = "Texture.Player.Body.Attack.Right";
				_shootDirection = "right";
				Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
				_time_to_pop_ms = texture->get_frame_duration_milliseconds() * texture->get_frame_count(); //reset the cooldown for determine length of shooting state duration
			}
			else if (input->is_button_state(Input::Button::SHOOTING_LEFT, Input::Button_State::DOWN))
			{
				_texture_id = "Texture.Player.Body.Attack.Left";
				_shootDirection = "left";
				Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
				_time_to_pop_ms = texture->get_frame_duration_milliseconds() * texture->get_frame_count(); //reset the cooldown for determine length of shooting state duration
			}
			else if (input->is_button_state(Input::Button::SHOOTING_UP, Input::Button_State::DOWN))
			{
				_texture_id = "Texture.Player.Body.Attack.Up";
				_shootDirection = "up";
				Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
				_time_to_pop_ms = texture->get_frame_duration_milliseconds() * texture->get_frame_count(); //reset the cooldown for determine length of shooting state duration
			}
			else if (input->is_button_state(Input::Button::SHOOTING_DOWN, Input::Button_State::DOWN))
			{
				_texture_id = "Texture.Player.Body.Attack.Down";
				_shootDirection = "down";
				Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
				_time_to_pop_ms = texture->get_frame_duration_milliseconds() * texture->get_frame_count(); //reset the cooldown for determine length of shooting state duration
			}

			std::cout << "time to pop " + std::to_string(_time_to_pop_ms) << std::endl;
			

			//shooting sounds
		}
		break;
	}
	}
}

void Player_Body::handle_exit_state(State state, Assets* assets)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);

	switch (state)
	{
	case State::Idle:
		break;
	case State::Walking:
		_isWalking = false; //set walking variable to false when not walking
		break;
	case State::Shooting:
		_isShooting = false; //set shooting variable to false when not shooting
		texture->reset(); // reset the animation
		break;
	}
}