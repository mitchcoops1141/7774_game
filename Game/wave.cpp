#include "wave.h"
#include "game_object.h"
#include "enemy.h"
#include "ranged_enemy.h"
#include <iostream>
#include <thread>
#include "text.h"
#include "hud.h"
#include "enemy_boss.h"
#include "ranged_enemy_boss.h"

Wave::Wave(std::string id)
	: Game_Object(id, "Texture.Player.Blank")
{
	_translation = Vector_2D(0, 0);
	_waveNumber = 0;
	_waveDuration = 2000;
	enemyCounter = 0;

	_shouldCreateHUD = true;
	_increaseStats = false;
}

Wave::~Wave()
{
}

void Wave::simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input*, Scene* scene, SDL_Renderer* renderer)
{
	if (_shouldCreateHUD) //check if should create HUD
	{
		scene->add_game_object(new HUD("HUD", renderer, scene)); //add hud
		_shouldCreateHUD = false; //set create hud to false
	}

	_waveDuration -= milliseconds_to_simulate; //reduce wave duration

	if (_waveDuration <= milliseconds_to_simulate) //when wave ended
	{
		//create color
		SDL_Color color;
		color.r = 16;
		color.g = 16;
		color.b = 16;
		color.a = 255;

		_waveNumber++; //increase wave number
		_increaseStats = true;
		startWave(assets, renderer, scene); //start next wave
		

		//create and render texts
		Game_Object* hud = scene->get_game_object("HUD"); //get the hud object
		hud->set_to_be_destroyed(true); //destroy hud at end of frame
		_shouldCreateHUD = true; //set should create hud to true
	}

	

	if (_waveNumber == 30)
	{
		if (enemyCounter == 170)
		{
			scene->get_game_object("Player")->set_to_be_destroyed(true); //destroy the player to casue end game
		}
	}
}

void Wave::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);

	if (_increaseStats) //when ready to increase stats
	{
		if (config->hardMode) //if hard mode
		{
			increasePlayerStat(scene); //increase player stat
			increasePlayerStat(scene); //increase player stat
			_increaseStats = false;
		}
		else //if easy mode
		{
			increasePlayerStat(scene); //increase player stat
			increasePlayerStat(scene); //increase player stat
			increasePlayerStat(scene); //increase player stat
			_increaseStats = false;
		}
	}
}

void Wave::startWave(Assets* assets, SDL_Renderer* renderer, Scene* scene)
{
	
	switch (_waveNumber)
	{
	case 1:
		//set waveDuration
		//spawn enemies
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		break;
	case 2:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1250), assets, renderer));
		enemyCounter++;
		break;
	case 3:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 0), assets, renderer));
		enemyCounter++;
		break;
	case 4:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 2400), assets, renderer));
		enemyCounter++;
		break;
	case 5:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 0), assets, renderer));
		enemyCounter++;
		break;
	case 6:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 2400), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 2400), assets, renderer));
		enemyCounter++;
		break;
	case 7:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 8:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 9:
		_waveDuration = 15000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1750, 0), assets, renderer));
		enemyCounter++;
		break;
	case 10:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 0), assets, renderer));
		enemyCounter++;	
		break;
	case 11:
		_waveDuration = 7000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 2000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1600), assets, renderer));
		enemyCounter++;
		break;
		//50
	case 12:
		_waveDuration = 7000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 2000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 13:
		_waveDuration = 5000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 2000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 14:
		_waveDuration = 5000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 200), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 15:
		_waveDuration = 5000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		break;
	case 16:
		_waveDuration = 7500;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		break;
	case 17:
		_waveDuration = 7500;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		break;
	case 18:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		break;
	case 19:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		break;
		//71
	case 20:
		_waveDuration = 12500;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 2000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 0), assets, renderer));
		enemyCounter++;
		break;
	case 21:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 22:
		_waveDuration = 5000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(1000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(1500, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 23:
		_waveDuration = 5000;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		break;
		//97
	case 24:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		break;
		//103
	case 25:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		break;
	case 26:
		_waveDuration = 12500;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		break;
	case 27:
		_waveDuration = 15000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(4000, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		break;
		//119
	case 28:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(300, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(600, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(900, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1800, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2100, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2400, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2700, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(300, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(600, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(900, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1200, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1800, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2100, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2400, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2700, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1500), assets, renderer));
		enemyCounter++;
		break;
		//149
	case 29:
		_waveDuration = 25000;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(0, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(1200, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(2400, 0), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(0, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(0, 1500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(0, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(1200, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(2400, 2500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy_Boss("enemy" + std::to_string(enemyCounter), Vector_2D(4000, 1500), assets, renderer));
		enemyCounter++;
		break;
		//161
	case 30:
		enemyCounter = 170;
		//170
		break;
	default:
		break;
	}
}

int Wave::getWave()
{
	return _waveNumber;
}

int Wave::getWaveDuration()
{
	return int(_waveDuration);
}

void Wave::increasePlayerStat(Scene* scene)
{
	Game_Object* player = scene->get_game_object("Player");
	if (!player)
	{
		return;
	}

	float random_number = ((float)_generator() / _generator.max()) * 5; //get random number between 1 and 5
	int stat_choice = int(random_number) + 1;

	if (stat_choice == 1) //increase speed
	{
		player->set_speed(player->speed() + 5);
	}
	else if (stat_choice == 2) //increase attack speed
	{
		player->set_attackSpeed(player->attackSpeed() - 3);
	}
	else if (stat_choice == 3) //increase projectile speed
	{
		player->set_projectileSpeed(player->projectile_speed() + 5);
	}
	else if (stat_choice == 4) //increase range
	{
		player->set_range(player->range() + 5);
	}
	else if (stat_choice == 5) //increase damage
	{
		player->set_attackDamage(player->attackDamage() + 2);
	}
}
