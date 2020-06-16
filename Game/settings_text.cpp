#include "settings_text.h"

Settings_Text::Settings_Text(std::string id, SDL_Renderer* renderer, Configuration* config)
	: Game_Object(id, "Texture.Player.Blank")
{
	_text_color.r = 255;
	_text_color.g = 255;
	_text_color.b = 255;
	_text_color.a = 255;


	std::string howToPlayTitle = "How To Play:";
	std::string howToPlayText = "WASD = Move. Arrow Keys = Shoot. Survive 30 rounds";
	std::string  difficultyTitle = "Set Difficulty: (space bar to change)";
	std::string  difficultyText;
	if (!(config->hardMode))
	{
		difficultyText = "Easy";
	}
	else
	{
		difficultyText = "Hard";
	}
	std::string  promptContinue = "Press Escape to go back to menu";

	_howToPlayTitle = new Text(renderer, howToPlayTitle.c_str(), _text_color, "ID");
	_howToPlayText = new Text(renderer, howToPlayText.c_str(), _text_color, "ID");
	_difficultyTitle = new Text(renderer, difficultyTitle.c_str(), _text_color, "ID");
	_difficultyText = new Text(renderer, difficultyText.c_str(), _text_color, "ID");
	_promptContinue = new Text(renderer, promptContinue.c_str(), _text_color, "ID");
}

Settings_Text::~Settings_Text()
{
	delete _howToPlayTitle;
	delete _howToPlayText;
	delete _difficultyTitle;
	delete _difficultyText;
	delete _promptContinue;
}

void Settings_Text::simulate_AI(Uint32, Assets*, Input*, Scene*, SDL_Renderer*)
{
}

void Settings_Text::render(Uint32, Assets*, SDL_Renderer* renderer, Configuration*, Scene*)
{
	_howToPlayTitle->render(renderer, Vector_2D(800, 100));
	_howToPlayText->render(renderer, Vector_2D(500, 200));
	_difficultyTitle->render(renderer, Vector_2D(600, 550));
	_difficultyText->render(renderer, Vector_2D(850, 650));
	_promptContinue->render(renderer, Vector_2D(675, 1000));
}
