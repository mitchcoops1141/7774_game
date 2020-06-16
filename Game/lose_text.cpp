#include "lose_text.h"
#include <iostream>

Lose_text::Lose_text(std::string id, SDL_Renderer* renderer, int wave_number)
	: Game_Object(id, "Texture.Player.Blank")
{
	_text_color.r = 255;
	_text_color.g = 255;
	_text_color.b = 255;
	_text_color.a = 255;

	std::cout << "LOSE TEXT CREATED" << std::endl;

	std::string loseText;

	if (wave_number == 30)
	{
		loseText = "Great Job, You Win!";
	}
	else
	{
		loseText = "Bad luck. You Lose.";
	}

	
	std::string waveNumber = "You reached wave: " + std::to_string(wave_number);
	std::string promptContinue = "Press Space to continue ";

	_loseText = new Text(renderer, loseText.c_str(), _text_color, "ID");
	_waveNumber = new Text(renderer, waveNumber.c_str(), _text_color, "ID");
	_continuePrompt = new Text(renderer, promptContinue.c_str(), _text_color, "ID");
}

Lose_text::~Lose_text()
{
	delete _loseText;
	delete _waveNumber;
	delete _continuePrompt;
}

void Lose_text::simulate_AI(Uint32, Assets*, Input*, Scene*, SDL_Renderer*)
{
}

void Lose_text::render(Uint32, Assets*, SDL_Renderer* renderer, Configuration*, Scene*)
{
	_loseText->render(renderer, Vector_2D(800, 400));
	_waveNumber->render(renderer, Vector_2D(800, 500));
	_continuePrompt->render(renderer, Vector_2D(800, 600));
}
