#include "spit_ball_boss.h"

Spit_Ball_Boss::Spit_Ball_Boss(std::string id, Scene* scene, Vector_2D spawn_location)
	: Game_Object(id, "Texture.Spit.Ball")
{
	Game_Object* player = scene->get_game_object("Player");
	if (!player)
	{
		return;
	}
	_width = 65;
	_height = 65;

	_speed = 0.62f;
	_range = 1000;

	_spawnLocation = spawn_location;
	_playerLocation = Vector_2D(player->translation().x() + player->width() / 2, player->translation().y() + player->height() / 2);
	_translation = _spawnLocation;

	_direction = (_playerLocation - _spawnLocation);
	_direction.normalize();
}

Spit_Ball_Boss::~Spit_Ball_Boss()
{
}

void Spit_Ball_Boss::simulate_AI(Uint32, Assets*, Input*, Scene * scene, SDL_Renderer*)
{
	Game_Object* player = scene->get_game_object("Player");
	if (!player)
	{
		return;
	}
	_velocity += _direction; //move towards the remove position
	_velocity.scale(_speed); //at the scale of the speed

	//if out of range. delete paper ball
	Vector_2D distanceToRemovePosition = (_translation - _spawnLocation); //get distance to remove position
	if (distanceToRemovePosition.magnitude() > _range) //if distance to remove position is > range
	{
		_to_be_destroyed = true;
	}

	//if hit player. hurt player. delete object
	Vector_2D distanceToPlayer = (_translation - Vector_2D(player->translation().x() + player->width() / 2, player->translation().y() + player->height() / 2));
	if (distanceToPlayer.magnitude() < player->collider().radius() * 1.5)
	{
		player->set_hp(player->hp() - 1); //subtract from player hp
		_to_be_destroyed = true;
	}
}

void Spit_Ball_Boss::render(Uint32 milliseconds_to_simulate, Assets * assets, SDL_Renderer * renderer, Configuration * config, Scene * scene)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config, scene);
}
