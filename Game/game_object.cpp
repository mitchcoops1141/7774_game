#pragma once

#include "game_object.h"
#include "text.h"


Game_Object::Game_Object(std::string id, std::string texture_id)
	: _translation(0, 0), _velocity(0, 0), _collider(0.0f, Vector_2D(0.f, 0.f))
{
	_id = id;
	_texture_id = texture_id;

	_width = 100;
	_height = 100;

	_flip = SDL_FLIP_NONE;
}
Game_Object::~Game_Object()
{
}

std::string Game_Object::id()
{
	return _id;
}

std::string Game_Object::texture_id()
{
	return _texture_id;
}

void Game_Object::simulate_physics(Uint32 milliseconds_to_simulate, Assets*, Scene* scene)
{
	Vector_2D velocity = _velocity;
	velocity.scale((float)milliseconds_to_simulate);

	_translation += velocity;

	for (Game_Object* game_object : scene->get_game_objects())
	{
		if (game_object->id() == _id)
		{
			continue;
		}

		Circle_2D collider = Circle_2D(_collider.radius(), _collider.translation() + _translation);
		Circle_2D other_collider = Circle_2D(game_object->_collider.radius(), game_object->_collider.translation() + game_object->_translation);
		float intersection_depth = collider.intersection_depth(other_collider);

		if (intersection_depth > 0.0f)
		{
			Vector_2D other_collider_to_collider = collider.translation() - other_collider.translation();
			other_collider_to_collider.normalize();
			other_collider_to_collider.scale(intersection_depth);
			_translation += other_collider_to_collider;

			Vector_2D collider_to_other_collider = other_collider.translation() - collider.translation();
			collider_to_other_collider.normalize();
			collider_to_other_collider.scale(intersection_depth);
			game_object->_translation += collider_to_other_collider;
		}
	}
}

void Game_Object::render(Uint32, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene)
{
	SDL_Rect destination;
	destination.x = (int)(_translation.x() - scene->camera_tranlsation().x());
	destination.y = (int)(_translation.y() - scene->camera_tranlsation().y());
	destination.w = _width;
	destination.h = _height;

	const float PI = 3.14159265f;
	if (_velocity.magnitude() > 0)
	{
		if (abs(_velocity.angle()) <= (PI / 2.f))
		{
			_flip = SDL_FLIP_NONE;
		}
		else
		{
			_flip = SDL_FLIP_HORIZONTAL;
		}
	}

	Texture* texture = (Texture*)assets->get_asset(_texture_id);
	texture->render(renderer, nullptr, &destination, _flip);

	if (config->should_display_ids)
	{
		SDL_Color text_color;
		text_color.r = 255;
		text_color.g = 255;
		text_color.b = 0;
		text_color.a = 255;

		Text id(renderer, _id.c_str(), text_color, "ID.Text");

		id.render(renderer, _translation + Vector_2D((float)_width / 2, (float)_height));
	}

	if (config->should_display_colliders && _collider.radius() > 0.f)
	{
		Texture* collider_texture = (Texture*)assets->get_asset("Texture.Collider");

		SDL_Rect collider_destination;
		collider_destination.x = (int)(_translation.x() + _collider.translation().x() - _collider.radius());
		collider_destination.y = (int)(_translation.y() + _collider.translation().y() - _collider.radius());
		collider_destination.w = (int)(_collider.radius() * 2.0f);
		collider_destination.h = (int)(_collider.radius() * 2.0f);

		collider_texture->render(renderer, nullptr, &collider_destination, SDL_FLIP_NONE);
	}
}

Vector_2D Game_Object::translation()
{
	return _translation;
}

Circle_2D Game_Object::collider()
{
	return _collider;
}

int Game_Object::width()
{
	return _width;
}

int Game_Object::height()
{
	return _height;
}

void Game_Object::set_translation(Vector_2D translation)
{
	_translation = translation;
}

void Game_Object::set_speed(float speed)
{
	_speed = speed;
}

float Game_Object::speed()
{
	return _speed;
}

void Game_Object::set_hp(int hp)
{
	_hp = hp; //set hp to given hp
}

int Game_Object::hp()
{
	return _hp;
}

void Game_Object::set_attackDamage(float attackDamage)
{
	_attackDamage = attackDamage;
}

float Game_Object::attackDamage()
{
	return _attackDamage;
}

void Game_Object::set_attackSpeed(float attackSpeed)
{
	_attackSpeed = attackSpeed;
}

float Game_Object::attackSpeed()
{
	return _attackSpeed;
}

void Game_Object::set_range(float range)
{
	_range = range;
}

float Game_Object::range()
{
	return _range;
}

void Game_Object::set_projectileSpeed(float projectile_speed)
{
	_projectileSpeed = projectile_speed;
}

float Game_Object::projectile_speed()
{
	return _projectileSpeed;
}
