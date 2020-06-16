#pragma once

#include "scene.h"

class Settings_Scene : public Scene
{
public:
	Settings_Scene();
	~Settings_Scene();

	virtual void update(SDL_Window* window) override;

};