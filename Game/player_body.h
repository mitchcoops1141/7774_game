#pragma once

#include "game_object.h"
#include <stack>
#include "player.h"
//#include "player.h"

class Player_Body : public Game_Object
{
public:
	Player_Body(std::string id);
	~Player_Body();

	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;
	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;

	enum class State
	{
		Idle,
		Walking,
		Shooting,
	};

	void push_state(State state, Assets* assets, Input* input);
	void pop_state(Assets* assets, Input* input);

private:
	void handle_enter_state(State state, Assets* assets, Input* input);
	void handle_exit_state(State state, Assets* assets);

	std::stack<State> _state;

	
	bool _isWalking = false; //variable to determine if player is walking
	bool _isShooting = false; //variable to determine if player is shooting
	int _shoot_cooldown_ms = 120; //variable to determine cooldown
	int _time_to_pop_ms; //variable to determine length of attacking animation
	std::string _shootDirection; //variable to get direction of shot
	std::string _ballID = "ball";
	int _ballCounter = 0;
};