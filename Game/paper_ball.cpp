#include "paper_ball.h"
#include <iostream>

Paper_Ball::Paper_Ball(std::string id, Scene* scene, std::string direction)
	: Game_Object(id, "Texture.Paper.Ball")
{
	Game_Object* player = scene->get_game_object("Player");
	if (!player)
	{
		return;
	}

	_width = 45;
	_height = 45;

	_speed = player->projectile_speed() / 100;
	_range = player->range() * 10;

	if (direction == "right") //if the ball is to move right
	{
		_translation = Vector_2D (player->translation().x() + player->width() / 2 + 25,
								  player->translation().y() + player->height() / 2 - 5); //determine spawn position
		_removePosition = Vector_2D(_translation.x() + _range, _translation.y()); //determine remove position
	}
	else if (direction == "left") //if the ball is to move left
	{
		_translation = Vector_2D(player->translation().x() + player->width() / 2 - 50, 
								 player->translation().y() + player->height() / 2 - 5); //determine spawn position
		_removePosition = Vector_2D(_translation.x() - _range, _translation.y()); //determine remove position
	}
	else if (direction == "up") //if the ball is to move up
	{
		_translation = Vector_2D(player->translation().x() + player->width() / 2 - 50, 
								 player->translation().y() + player->height() / 2 - 18); //determine spawn position
		_removePosition = Vector_2D(_translation.x(), _translation.y() - _range); //determine remove position
	}
	else if (direction == "down") //if the ball is to move down
	{
		_translation = Vector_2D(player->translation().x() + player->width() / 2 + 10, 
								 player->translation().y() + player->height() / 2 + 22); //determine spawn position
		_removePosition = Vector_2D(_translation.x(), _translation.y() + _range); //determine remove position
	}
}

Paper_Ball::~Paper_Ball()
{
}

void Paper_Ball::simulate_AI(Uint32, Assets*, Input*, Scene*, SDL_Renderer*)
{	
	Vector_2D direction = (_removePosition - _translation); //get direction to the remove position
	direction.normalize(); //normalize position
	_velocity += direction; //move towards the remove position
	_velocity.scale(_speed); //at the scale of the speed

	//if out of range. delete paper ball
	Vector_2D distanceToRemovePosition = (_translation - _removePosition); //get distance to remove position
	if (distanceToRemovePosition.magnitude() < 5) //if its less then 5 pixels away (close enough to range number)
	{
		_to_be_destroyed = true;
	}
}

void Paper_Ball::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
