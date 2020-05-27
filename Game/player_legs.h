#pragma once

#include "game_object.h"
#include "player.h"

#include <stack>

class Player_Legs : public Game_Object
{
public:
	Player_Legs(std::string id);
	~Player_Legs();

	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;

	enum class State
	{
		Idle,
		Walking
	};

	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	std::stack<State> _state;

	bool _isWalking;
};