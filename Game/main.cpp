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
#include "hud.h"
#include "lose_scene.h"
#include "lose_text.h"

#include <stack>

int main(void)
{
	Configuration* config = new Configuration(); //create config object
	Engine* engine = new Engine("Game", config); //create engine object
	Assets* assets = new Assets(engine->renderer()); //create assets object
	Input* input = new Input(); //create input object
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

	bool menuScene = true;
	bool gameScene = false;
	bool loseScene = false;

	int waveNumber = 0;
	//main game loop
	while(!input->is_button_state(Input::Button::QUIT, Input::Button_State::PRESSED))
	{
		if (menuScene)
		{
			if ((menu_buttons->texture_id() == "Texture.Menu.Start") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//go to game scene
				scenes.push(new Game_Scene());
				Sound* sound = (Sound*)assets->get_asset("Sound.Music");
				Mix_PlayChannel(0, sound->data(), -1);
				Mix_Volume(0, MIX_MAX_VOLUME / 8);
				menuScene = false;
				gameScene = true;
				loseScene = false;
			}
			else if ((menu_buttons->texture_id() == "Texture.Menu.Settings") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//go to settings scene
			}
			else if ((menu_buttons->texture_id() == "Texture.Menu.Exit") && input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				//exit game
				exit(0);
			}
		}
		else if (gameScene)
		{
			waveNumber = scenes.top()->get_game_object("Wave")->waveNumber(); //keep track of the wave number to pass into the lose / win text later	
		}
		else if (loseScene)
		{
			if (input->is_button_state(Input::Button::SPACE, Input::Button_State::PRESSED))
			{
				scenes.pop();
				gameScene = false;
				menuScene = true;
				loseScene = false;
			}
		}
		Uint32 previous_frame_duration = frame_end_time_ms - frame_start_time_ms;
		frame_start_time_ms            = SDL_GetTicks();

		scenes.top()->update(engine->window());
		input->get_input(); //call input: get_input to get players inputs whenever they press something
		editor->update(input, scenes.top(), config); //update the editor by passing in the input scene and config objects
		engine->simulate(previous_frame_duration, assets, scenes.top(), input, config, engine->renderer()); //simulate scene

		//check if game object to be destroyed:
		std::vector<Game_Object*> game_objects = scenes.top()->get_game_objects();
		for (Game_Object* game_object : game_objects)
		{
			if (game_object->to_be_destroyed())
			{
				if (!(game_object->id() == "Player")) //if not the player
				{
					scenes.top()->remove_game_object(game_object->id());
					delete game_object;
				}
				else //if it is the player
				{
					scenes.top()->remove_game_object(game_object->id());
					delete game_object;
					scenes.pop();
					scenes.push(new Lose_scene());
					scenes.top()->add_game_object(new Lose_text("Lose.Text", engine->renderer(), waveNumber));
					gameScene = false;
					menuScene = false;
					loseScene = true;
				}
				
			}
		}

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