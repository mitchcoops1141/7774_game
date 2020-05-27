#include "menu_buttons.h"

Menu_Buttons::Menu_Buttons(std::string id)
	: Game_Object(id, "Texture.Menu.Start")
{
	//Put all text in one photo
	//have a texture for if Start selected, a texture for if Settings selected, a texture for if Exit selected.
	//in this class have a enum class with START, SETTINGS, EXIT
	//change texture depending on enum
	//get input of space bar
	//go to scene of whenever spacebar is clicked
	_width = 1920;
	_height = 1040;

	_state.push(State::Start);
}

Menu_Buttons::~Menu_Buttons()
{
}

void Menu_Buttons::simulate_AI(Uint32, Assets* assets, Input* input, Scene*, SDL_Renderer*)
{
	
	switch (_state.top())
	{
	case State::Start:
		if (input->is_button_state(Input::Button::DOWN, Input::Button_State::PRESSED))
		{
			push_state(State::Settings, assets, input);
		}
		break;
	case State::Settings:
		if (input->is_button_state(Input::Button::UP, Input::Button_State::PRESSED))
		{
			push_state(State::Start, assets, input);
		}
		if (input->is_button_state(Input::Button::DOWN, Input::Button_State::PRESSED))
		{
			push_state(State::Exit, assets, input);
		}
		break;
	case State::Exit:	
		if (input->is_button_state(Input::Button::UP, Input::Button_State::PRESSED))
		{
			push_state(State::Settings, assets, input);
		}
		break;
	}
}

void Menu_Buttons::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Menu_Buttons::push_state(State state, Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets, input);
}

void Menu_Buttons::pop_state(Assets* assets, Input* input)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets, input);
}

void Menu_Buttons::handle_enter_state(State state, Assets*, Input*)
{
	switch (state)
	{
	case State::Start:
		_texture_id = "Texture.Menu.Start";
		break;
	case State::Settings:
		_texture_id = "Texture.Menu.Settings";
		break;
	case State::Exit:
		_texture_id = "Texture.Menu.Exit";
		break;
	}
}

void Menu_Buttons::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::Start:
		break;
	case State::Settings:
		break;
	case State::Exit:
		break;
	}
}
