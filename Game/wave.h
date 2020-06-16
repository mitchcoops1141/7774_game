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

	int getWave();
	int getWaveDuration();

	void increasePlayerStat(Scene* scene);

private:

	int _seed;
	std::minstd_rand0 _generator;

	int enemyCounter = 0;

	SDL_Color _hud_text_color;

	bool _shouldCreateHUD;
	bool _increaseStats;

	std::vector<Game_Object*> _game_objects;
};