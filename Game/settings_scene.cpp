#include "settings_scene.h"

Settings_Scene::Settings_Scene()
	: Scene("Settings")
{
	_background_color.r = 70;
	_background_color.g = 130;
	_background_color.b = 60;
}

Settings_Scene::~Settings_Scene()
{
	//get_game_object("Settings.Text")->set_to_be_destroyed(true);
}

void Settings_Scene::update(SDL_Window*)
{
}
