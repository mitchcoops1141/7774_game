#include "hud.h"
#include "text.h"
#include "player.h"
#include "wave.h"

HUD::HUD(std::string id, SDL_Renderer* renderer, Scene* scene)
	: Game_Object(id, "Texture.Player.Blank")
{
	_hud_color.r = 16;
	_hud_color.g = 16;
	_hud_color.b = 16;
	_hud_color.a = 255;

	Game_Object* player = scene->get_game_object("Player");
	if (!player)
	{
		return;
	}

	//create strings for each attribute
	std::string waveNumberText = "WAVE: " + std::to_string(scene->get_game_object("Wave")->waveNumber());
	std::string playerSpeedText = "SPEED: " + std::to_string(int(player->speed()));
	std::string playerHpText = "HP: " + std::to_string(player->hp());
	std::string playerDmgText = "DMG: " + std::to_string(player->attackDamage());
	std::string playerAtkSpdText = "ATK SPD: " + std::to_string(player->attackSpeed());
	std::string playerRangeText = "RANGE: " + std::to_string(player->range());
	std::string playerProjSpdText = "PROJ SPD: " + std::to_string(int(player->projectile_speed()));

	//create text objects
	_waveNumberText = new Text(renderer, waveNumberText.c_str(), _hud_color, "ID");
	_playerSpeedText = new Text(renderer, playerSpeedText.c_str(), _hud_color, "ID");
	_playerHpText = new Text(renderer, playerHpText.c_str(), _hud_color, "ID");
	_playerDmgText = new Text(renderer, playerDmgText.c_str(), _hud_color, "ID");
	_playerAtkSpdText = new Text(renderer, playerAtkSpdText.c_str(), _hud_color, "ID");
	_playerRangeText = new Text(renderer, playerRangeText.c_str(), _hud_color, "ID");
	_playerProjSpdText = new Text(renderer, playerProjSpdText.c_str(), _hud_color, "ID");
}

HUD::~HUD()
{
	//delete text objects
	delete _waveNumberText;
	delete _playerSpeedText;
	delete _playerHpText;
	delete _playerDmgText;
	delete _playerAtkSpdText;
	delete _playerRangeText;
	delete _playerProjSpdText;
}

void HUD::simulate_AI(Uint32, Assets*, Input*, Scene*, SDL_Renderer*)
{
}

void HUD::render(Uint32, Assets*, SDL_Renderer* renderer, Configuration*, Scene*)
{
	//render text objects
	_waveNumberText->render(renderer, Vector_2D(25, 25));
	_playerHpText->render(renderer, Vector_2D(25, 300));
	_playerSpeedText->render(renderer, Vector_2D(25, 400));
	_playerDmgText->render(renderer, Vector_2D(25, 500));
	_playerAtkSpdText->render(renderer, Vector_2D(25, 600));
	_playerRangeText->render(renderer, Vector_2D(25, 700));
	_playerProjSpdText->render(renderer, Vector_2D(25, 800));
}