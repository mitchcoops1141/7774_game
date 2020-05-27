#pragma once

#include "game_object.h"
#include "assets.h"
#include "sound.h"
#include <stack>


class Enemy : public Game_Object
{
public:
	Enemy(std::string id);
	~Enemy();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	virtual void set_hp(int hp) override;
	

	enum class State
	{
		walking,
		agro,
		hurt,
		dead
	};

	void push_state(State state, Assets* assets, Input* input);
	void pop_state(Assets* assets, Input* input);


private:
	void handle_enter_state(State state, Assets* assets, Input* input);
	void handle_exit_state(State state, Assets* assets);

	std::stack<State> _state;
	float _deathAnimationTimer_ms = 14 * 100;
	int _hurtColorTimer_ms = 250;
	float _knockback;
	bool _isDead;
};