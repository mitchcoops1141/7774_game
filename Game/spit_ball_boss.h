#pragma once

#include "game_object.h"
#include "assets.h"


class Spit_Ball_Boss : public Game_Object
{
public:
	Spit_Ball_Boss(std::string id, Scene* scene, Vector_2D spawn_location);
	~Spit_Ball_Boss();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	Vector_2D _removePosition = Vector_2D(0, 0);
	Vector_2D _direction = Vector_2D(0, 0);
	Vector_2D _spawnLocation = Vector_2D(0, 0);
	Vector_2D _playerLocation = Vector_2D(0, 0);
};