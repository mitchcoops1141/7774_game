#include <SDL.h>
#include <string>
#include "Scene.h"
#include "game_object.h"
#include "text.h"

class Settings_Text : public Game_Object
{
public:
	Settings_Text(std::string id, SDL_Renderer* renderer, Configuration* config);
	~Settings_Text();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	SDL_Color _text_color;
	Text* _howToPlayTitle;
	Text* _howToPlayText;
	Text* _difficultyTitle;
	Text* _difficultyText;
	Text* _promptContinue;

	std::string _textWaveNumber;
};