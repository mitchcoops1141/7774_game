#include "paper_ball.h"

Paper_Ball::Paper_Ball(std::string id)
	: Game_Object(id, "Texture.Paper.Ball")
{
	_width = 20;
	_height = 20;

	_translation = Vector_2D(200, 200);
}

Paper_Ball::~Paper_Ball()
{
}

void Paper_Ball::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}

void Paper_Ball::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
