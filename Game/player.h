#pragma once

#include "game_object.h"
#include "assets.h"
#include "sound.h"
#include <stack>


class Player : public Game_Object
{
public:
	Player(std::string id);
	~Player();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	virtual void set_hp(int hp) override;

	enum class State
	{
		Alive,
		Hurt,
		Dead,
	};

	void push_state(State state, Assets* assets, Input* input);
	void pop_state(Assets* assets, Input* input);


private:
	void handle_enter_state(State state, Assets* assets, Input* input);
	void handle_exit_state(State state, Assets* assets);

	std::stack<State> _state;

	float _invincibilityCooldown_ms = 750.f;

	bool _isHurt = false;
};