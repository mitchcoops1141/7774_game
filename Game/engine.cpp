#include "engine.h"

#include <iostream>
#include <algorithm>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "texture.h"
#include "animated_texture.h"
#include "game_object.h"

Engine::Engine(std::string window_name, Configuration* config)
{
	const int init_result         = SDL_Init(SDL_INIT_EVERYTHING); //initialise SDL 
	const int init_result_success = 0; //validation test
	if(init_result != init_result_success) //check if initialisation was successful
	{
		std::cout << "Failed to initialize SDL" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	//window properties
	const char* game_title = window_name.c_str(); //set title of the window
	const int x            = 0; //set width of the window
	const int y            = 0; //set hight of the window
	_window = SDL_CreateWindow(game_title, x, y, config->window_width, config->window_height, SDL_WINDOW_FULLSCREEN_DESKTOP); //create the window
	if(_window == nullptr) //check if window creation was a success
	{
		std::cout << "Failed to create SDL window" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int first_renderer = -1; //render variable
	_renderer = SDL_CreateRenderer(_window, first_renderer, 0); //render window
	if(_renderer == nullptr) //check if render was success
	{
		std::cout << "Failed to create Renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int image_init_result  = IMG_Init(IMG_INIT_PNG); //initialize image
	const int image_init_success = IMG_INIT_PNG; //validation
	if(image_init_result != image_init_success) //check if image was initialized
	{
		std::cout << "Failed to initialize SDL Image" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int ttf_init_result = TTF_Init(); //render font
	const int ttf_init_success = 0; //validation
	if (ttf_init_result != ttf_init_result) //check if font was rendered
	{
		std::cout << "Failed to initialize SDL TTF" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	const int mixer_init_result = Mix_Init(MIX_INIT_MOD); //initialize mixer
	const int mixer_init_failure = 0; //validation
	if (mixer_init_result == mixer_init_failure)
	{
		std::cout << "Failed to initialize SDL Mixer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError() << std::endl;
		exit(1);
	}

	const int mixer_open_audio_result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024); //open the audio
	const int mixer_open_audio_success = 0; //validation
	if (mixer_open_audio_result != mixer_open_audio_success)
	{
		std::cout << "Failed to open audio" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	Mix_AllocateChannels(3); //open 3 channels
}

Engine::~Engine()
{
}

void Engine::simulate(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input, Configuration* config)
{
	simulate_AI(milliseconds_to_simulate, assets, scene, input); //call simulate AI function
	simulate_physics(milliseconds_to_simulate, assets, scene); //call simulate Physics function
	render(milliseconds_to_simulate, assets, scene, config); //call render function
}

void Engine::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Input* input)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects(); //get all game objects
	for (Game_Object* game_object : game_objects) //loop through game objects
	{
		game_object->simulate_AI(milliseconds_to_simulate, assets, input, scene); //for each objects call the simulate AI function
	}
}

void Engine::simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene)
{
	std::vector<Game_Object*> game_objects = scene->get_game_objects(); //get all game objects
	for (Game_Object* game_object : game_objects) //loop through game objects
	{
		game_object->simulate_physics(milliseconds_to_simulate, assets, scene); //for each object call the simulate Physics function
	}
}

void Engine::render(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene, Configuration* config)
{
	const int render_clear_success = 0; //validation
	const int render_clear_result  = SDL_RenderClear(_renderer); //clear render	
	if(render_clear_result != render_clear_success) //check if render clear was successful
	{
		std::cout << "Failed to clear renderer" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	//window background properties
	const SDL_Color background = scene->background_color();
	const int render_color_success = 0; //validation
	const int render_color_result  = SDL_SetRenderDrawColor(_renderer, background.r, background.g, background.b, 255); //create window background
	if(render_color_result != render_color_success) //check if color set was successful
	{
		std::cout << "Failed to set render color" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	//get game objects and render them
	std::vector<Game_Object*> sorted_game_objects = scene->get_game_objects(); //get game objetcs
	const struct
	{
		bool operator()(Game_Object* a, Game_Object* b)
		{
			return a->translation().y() < b->translation().y();
		}
	} sort_by_y_order;
	std::sort(sorted_game_objects.begin(), sorted_game_objects.end(), sort_by_y_order);

	for (Game_Object* game_object : sorted_game_objects)
	{
		game_object->render(milliseconds_to_simulate, assets, _renderer, config, scene);
	}

	SDL_RenderPresent(_renderer); //render everything
}

SDL_Renderer* Engine::renderer()
{
	return _renderer;
}

SDL_Window* Engine::window()
{
	return _window;
}