#pragma once

#include "Scene.h"
#include "text.h"
#include "assets.h"
#include "menu_buttons.h"


class Menu_Scene : public Scene
{
public:
	Menu_Scene();
	~Menu_Scene();

	virtual void update(SDL_Window* window) override;
};