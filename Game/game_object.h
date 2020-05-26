#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>

#include "assets.h"
#include "input.h"
#include "vector_2D.h"
#include "configuration.h"
#include "circle_2D.h"
#include "Scene.h"


class Game_Object
{
public:
	Game_Object(std::string id, std::string texture_id);
	virtual ~Game_Object();

	std::string id();
	std::string texture_id();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene);

	Vector_2D translation();
	Circle_2D collider();

	int width();
	int height();

	void set_translation(Vector_2D translation);

	Vector_2D velocity();

	void set_speed(float speed);
	float speed();

	virtual void set_hp(int hp);
	int hp();

	void set_attackDamage(float attackDamage);
	float attackDamage();

	void set_attackSpeed(float attackSpeed);
	float attackSpeed();

	void set_range(float range);
	float range();

	void set_projectileSpeed(float projectile_speed);
	float projectile_speed();

protected:
	std::string _id;
	std::string _texture_id;

	Vector_2D _translation;
	Vector_2D _velocity;

	Circle_2D _collider;

	int _width;
	int _height;

	SDL_RendererFlip _flip;


	//player and enemy attributes
	float _speed;
	int _hp;
	float _attackDamage;
	float _attackSpeed;
	float _range;
	float _projectileSpeed;
};