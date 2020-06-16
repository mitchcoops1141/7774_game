#include "lose_scene.h"
#include "lose_text.h"
#include "game_scene.h"
#include <iostream>

Lose_scene::Lose_scene()
	: Scene("Game")
{
	//add objects
	
}

Lose_scene::~Lose_scene()
{
	get_game_object("Lose.Text")->set_to_be_destroyed(true);
}

void Lose_scene::update(SDL_Window*)
{
	_background_color.r = 0;
	_background_color.g = 0;
	_background_color.b = 0;
}
