#pragma once

#include "game_object.h"
#include "assets.h"
#include "sound.h"
#include <stack>
#include <random>
#include <time.h>


class Wave : public Game_Object
{
public:
	Wave(std::string id);
	~Wave();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	void startWave(Assets* assets, SDL_Renderer* renderer, Scene* scene);

private:

	int _seed;
	std::minstd_rand0 _generator;

	int _waveNumber;
	Uint32 _waveDuration = 2000;

	int enemyCounter = 1;
};