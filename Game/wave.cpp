#include "wave.h"
#include "game_object.h"
#include "enemy.h"
#include "ranged_enemy.h"
#include <iostream>
#include <thread>

Wave::Wave(std::string id)
	: Game_Object(id, "Texture.Player.Blank")
{
	_translation = Vector_2D(0, 0);
	_waveNumber = 1;
}

Wave::~Wave()
{
}

void Wave::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene, SDL_Renderer* renderer)
{
	//std::cout << std::to_string(_waveDuration) << std::endl;
	//std::cout << std::to_string(_waveNumber) << std::endl;

	_waveDuration -= milliseconds_to_simulate;

	if (_waveDuration <= milliseconds_to_simulate)
	{
		startWave( assets, renderer, scene);
		_waveNumber++;
	}
}

void Wave::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}

void Wave::startWave(Assets* assets, SDL_Renderer* renderer, Scene* scene)
{
	float random_number = ((float)_generator() / _generator.max()) * 5; //get random number between 1 and 5
	std::cout << std::to_string(round(random_number)) << std::endl;
	int wave_choice = int(random_number) + 1;

	switch (wave_choice)
	{
	case 1:
		//set waveDuration
		//spawn enemies
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 2:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 3:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 500), assets, renderer));
		enemyCounter++;

		break;
	case 4:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 1800), assets, renderer));
		enemyCounter++;
		break;
	case 5:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 1800), assets, renderer));
		enemyCounter++;
		break;
	default:
		break;
	}
}
