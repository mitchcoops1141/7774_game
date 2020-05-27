#pragma once

#include "game_object.h"
#include "assets.h"
#include "sound.h"


class Background : public Game_Object
{
public:
	Background(std::string id);
	~Background();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
};