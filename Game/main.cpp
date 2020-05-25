#include <iostream>
#include <chrono>
#include <thread>

#include "engine.h"
#include "assets.h"
#include "game_scene.h"
#include "input.h"
#include "editor.h"
#include "configuration.h"
#include "menu_scene.h"
#include "menu_buttons.h"
#include "enemy.h"

#include <stack>

int main(void)
{
	Configuration* config = new Configuration(); //create config object
	Engine* engine = new Engine("Game", config); //create engine object
	Assets* assets = new Assets(engine->renderer()); //create assets object
	Input* input = new Input(); //create input object
	//Scene* game_scene = new Game_Scene(); //create scene object
	Editor* editor = new Editor(L"Game"); //object


	std::stack<Scene*> scenes;
	scenes.push(new Menu_Scene());
	
	Game_Object* menu_buttons = scenes.top()->get_game_object("Menu");

	

	//calculate frames
	const Uint32 milliseconds_per_seconds = 1000;
	const Uint32 frames_per_second        = 60;
	const Uint32 frame_time_ms            = milliseconds_per_seconds / frames_per_second;

	Uint32 frame_start_time_ms = 0;
	Uint32 frame_end_time_ms   = frame_time_ms;

	bool gameScene = true;
	//main game loop
	while(!input->is_button_state(Input::Button::QUIT, Input::Button_State::PRESSED))
	{
		if (gameScene)
		{
			if ((menu_buttons->texture_id() == "Texture.Menu.Start") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//go to game scene
				std::cout << "STARTING LEVEL" << std::endl;
				scenes.push(new Game_Scene());
				gameScene = false;
			}
			else if ((menu_buttons->texture_id() == "Texture.Menu.Settings") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//go to settings scene
			}
			else if ((menu_buttons->texture_id() == "Texture.Menu.Exit") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//exit game
			}
		}
		Uint32 previous_frame_duration = frame_end_time_ms - frame_start_time_ms;
		frame_start_time_ms            = SDL_GetTicks();

		scenes.top()->update(engine->window());
		input->get_input(); //call input: get_input to get players inputs whenever they press something
		editor->update(input, scenes.top(), config); //update the editor by passing in the input scene and config objects
		engine->simulate(previous_frame_duration, assets, scenes.top(), input, config); //simulate scene

		//calculate frames
		const Uint32 current_time_ms   = SDL_GetTicks();
		const Uint32 frame_duration_ms = current_time_ms - frame_start_time_ms;
		if(frame_duration_ms < frame_time_ms)
		{
			const Uint32 time_to_sleep_for = frame_time_ms - frame_duration_ms;
			std::this_thread::sleep_for(std::chrono::milliseconds(time_to_sleep_for));
		}

		frame_end_time_ms = SDL_GetTicks();
	}

	return 0;
}