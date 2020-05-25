#pragma once

#include "game_object.h"
#include "assets.h"


class Paper_Ball : public Game_Object
{
public:
	Paper_Ball(std::string id);
	~Paper_Ball();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
};