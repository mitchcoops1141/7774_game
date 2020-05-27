#include <SDL.h>
#include <string>
#include "Scene.h"
#include "game_object.h"

class HUD : public Game_Object
{
public:
	HUD(std::string id);
	~HUD();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

	
private:
	SDL_Color _hud_text_color;

	std::string _health;
	std::string _attackDamage;
	std::string _attackSpeed;
	std::string _projectileSpeed;
	std::string _speed;
	std::string _range;
};