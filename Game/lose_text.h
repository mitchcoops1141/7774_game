#include <SDL.h>
#include <string>
#include "Scene.h"
#include "game_object.h"
#include "text.h"

class Lose_text : public Game_Object
{
public:
	Lose_text(std::string id, SDL_Renderer* renderer, int wave_number);
	~Lose_text();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, SDL_Renderer* renderer) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config, Scene* scene) override;

private:
	SDL_Color _text_color;
	Text* _loseText;
	Text* _waveNumber;
	Text* _continuePrompt;

	std::string _textWaveNumber;
};