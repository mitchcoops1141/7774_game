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
	void set_texture_id(std::string texture_id);

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) = 0;
	virtual void simulate_physics(Uint32 milliseconds_to_simulate, Assets* assets, Scene* scene);
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene);

	Vector_2D translation();
	Circle_2D collider();

	int width();
	int height();

	void set_translation(Vector_2D translation);

	Vector_2D velocity();

	void set_to_be_destroyed(bool to_be_destroyed);
	bool to_be_destroyed();

	void set_speed(float speed);
	float speed();

	virtual void set_hp(int hp);
	int hp();

	void set_attackDamage(int attackDamage);
	int attackDamage();

	void set_attackSpeed(int attackSpeed);
	int attackSpeed();

	void set_range(int range);
	int range();

	void set_projectileSpeed(float projectile_speed);
	float projectile_speed();

	int waveNumber();
	Uint32 waveDuration();

protected:
	std::string _id;
	std::string _texture_id;

	Vector_2D _translation;
	Vector_2D _velocity;

	Circle_2D _collider;

	int _width;
	int _height;

	SDL_RendererFlip _flip;

	bool _to_be_destroyed;

	Uint32 _spawnDamageTimer;

	//wave attributes
	int _waveNumber;
	Uint32 _waveDuration;

	//player and enemy attributes
	float _speed;
	int _hp;
	int _attackDamage;
	int _attackSpeed;
	int _range;
	float _projectileSpeed;
};