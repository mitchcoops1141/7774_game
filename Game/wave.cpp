#include "wave.h"
#include "game_object.h"
#include "enemy.h"
#include "ranged_enemy.h"
#include <iostream>
#include <thread>
#include "text.h"
#include "hud.h"
#include "enemy_boss.h"

Wave::Wave(std::string id)
	: Game_Object(id, "Texture.Player.Blank")
{
	_translation = Vector_2D(0, 0);
	_waveNumber = 0;
	_waveDuration = 2000;

	_shouldCreateHUD = true;
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
		startWave(assets, renderer, scene); //start next wave
		increasePlayerStat(scene); //increase player stat

		//create and render texts
		Game_Object* hud = scene->get_game_object("HUD"); //get the hud object
		hud->set_to_be_destroyed(true); //destroy hud at end of frame
		_shouldCreateHUD = true; //set should create hud to true
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
	
	switch (_waveNumber)
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
		break;
	case 3:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 500), assets, renderer));
		enemyCounter++;
		break;
	case 4:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2500, 1800), assets, renderer));
		enemyCounter++;
		break;
	case 5:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 500), assets, renderer));
		enemyCounter++;
		break;
	case 6:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 1800), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(2000, 1800), assets, renderer));
		enemyCounter++;
		break;
	case 7:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 8:
		_waveDuration = 10000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3500, 1500), assets, renderer));
		enemyCounter++;
		break;
	case 9:
		_waveDuration = 15000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(500, 1250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(750, 1000), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 750), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1500, 500), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1750, 250), assets, renderer));
		enemyCounter++;
		break;
	case 10:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 300), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1000, 900), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 450), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(1250, 750), assets, renderer));
		enemyCounter++;	
		break;
	case 11:
		_waveDuration = 7000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 12:
		_waveDuration = 7000;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Ranged_Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 13:
		_waveDuration = 5000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 14:
		_waveDuration = 5000;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 1600), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(3200, 250), assets, renderer));
		enemyCounter++;
		scene->add_game_object(new Enemy("enemy" + std::to_string(enemyCounter), Vector_2D(250, 1600), assets, renderer));
		enemyCounter++;
		break;
	case 15:
		_waveDuration = 5000;
		break;
	case 16:
		_waveDuration = 10000;
		scene->add_game_object(new Enemy_Boss("enemy.boss" + std::to_string(enemyCounter), Vector_2D(3200, 900), assets, renderer));
		enemyCounter++;
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

	float random_number = ((float)_generator() / _generator.max()) * 6; //get random number between 1 and 5
	int stat_choice = int(random_number) + 1;

	if (stat_choice == 1) //increase speed
	{
		player->set_speed(player->speed() + 5);
	}
	else if (stat_choice == 2) //increase HP
	{
		player->set_hp(player->hp() + 1);
	}
	else if (stat_choice == 3) //increase attack speed
	{
		player->set_attackSpeed(player->attackSpeed() - 3);
	}
	else if (stat_choice == 4) //increase projectile speed
	{
		player->set_projectileSpeed(player->projectile_speed() + 5);
	}
	else if (stat_choice == 5) //increase range
	{
		player->set_range(player->range() + 5);
	}
	else if (stat_choice == 6) //increase damage
	{
		player->set_attackDamage(player->attackDamage() + 2);
	}
}
