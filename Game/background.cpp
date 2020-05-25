#include "background.h"

Background::Background(std::string id)
	: Game_Object(id, "Texture.Background")
{
	_width = 3840;
	_height = 2160;

	_translation = Vector_2D(0, 0);
}

Background::~Background()
{
}

void Background::simulate_AI(Uint32 , Assets* , Input* , Scene* )
{
}

void Background::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	//Texture* texture = (Texture*)assets->get_asset(_texture_id);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
