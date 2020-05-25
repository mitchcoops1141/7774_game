#pragma once

#include "game_object.h"
#include "assets.h"


class Paper_Ball : public Game_Object
{
public:
	Paper_Ball(std::string id, Scene* scene, std::string direction);
	~Paper_Ball();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	Vector_2D _removePosition = Vector_2D(0,0);
};