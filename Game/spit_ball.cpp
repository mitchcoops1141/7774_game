#include "Spit_ball.h"

Spit_Ball::Spit_Ball(std::string id, Scene* scene, Vector_2D spawn_location)
	: Game_Object(id, "Texture.Spit.Ball")
{
	Game_Object* player = scene->get_game_object("Player");
	_width = 35;
	_height = 35;

	_speed = player->projectile_speed() / 150;
	_range = player->range() * 15;
	
	_spawnLocation = spawn_location;
	_playerLocation = Vector_2D(player->translation().x() + player->width() / 2, player->translation().y() + player->height() / 2);
	_translation = _spawnLocation;

	_direction = (_playerLocation - _spawnLocation);
	_direction.normalize();
}

Spit_Ball::~Spit_Ball()
{
}

void Spit_Ball::simulate_AI(Uint32, Assets*, Input*, Scene* scene, SDL_Renderer*)
{
	Game_Object* player = scene->get_game_object("Player");
	_velocity += _direction; //move towards the remove position
	_velocity.scale(_speed); //at the scale of the speed

	//if out of range. delete paper ball
	Vector_2D distanceToRemovePosition = (_translation - _spawnLocation); //get distance to remove position
	if (distanceToRemovePosition.magnitude() > _range) //if distance to remove position is > range
	{
		scene->remove_game_object(this->id()); //remove this object
	}

	//if hit player. hurt player. delete object
	Vector_2D distanceToPlayer = (_translation - Vector_2D(player->translation().x() + player->width() / 2, player->translation().y() + player->height() / 2));
	if (distanceToPlayer.magnitude() < player->collider().radius() * 2)
	{
		player->set_hp(player->hp() - 1); //subtract from player hp
		scene->remove_game_object(this->id()); //remove this object
	}
}

void Spit_Ball::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
