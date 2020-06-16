#pragma once

#include "scene.h"

class Lose_scene : public Scene
{
public:
	Lose_scene();
	~Lose_scene();

	virtual void update(SDL_Window* window) override;

};