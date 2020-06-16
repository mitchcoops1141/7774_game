#include <SDL.h>
#include <string>
#include "Scene.h"
#include "game_object.h"
#include "text.h"

class HUD : public Game_Object
{
public:
	HUD(std::string id, SDL_Renderer* renderer, Scene* scene);
	~HUD();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	SDL_Color _hud_color;
	Text* _waveNumberText;
	Text* _playerSpeedText;
	Text* _playerHpText;
	Text* _playerDmgText;
	Text* _playerAtkSpdText;
	Text* _playerRangeText;
	Text* _playerProjSpdText;


};