#include "menu_scene.h"

Menu_Scene::Menu_Scene()
	: Scene("Menu")
{
	_background_color.r = 70;
	_background_color.g = 130;
	_background_color.b = 60;

	//Menu Text Object
	add_game_object(new Menu_Buttons("Menu"));
}

Menu_Scene::~Menu_Scene()
{
}

void Menu_Scene::update(SDL_Window*)
{
}
