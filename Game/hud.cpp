#include "hud.h"
#include "text.h"
#include "player.h"
#include "wave.h"

HUD::HUD(std::string id)
	: Game_Object(id, "Texture.Player.Blank")
{
	_hud_text_color.r = 16;
	_hud_text_color.g = 16;
	_hud_text_color.b = 16;
	_hud_text_color.a = 255;
}

HUD::~HUD()
{
}

void HUD::simulate_AI(Uint32, Assets*, Input*, Scene* scene, SDL_Renderer*)
{
	Game_Object* player = scene->get_game_object("Player"); //get player

	_health = "HP: " + std::to_string(player->hp()) + //set a string for the palyers health
		"         Dmg: " + std::to_string((int)round(player->attackDamage())) +
		"         Atk Spd: " + std::to_string((int)round(player->attackSpeed())) +
		"         Proj Spd: " + std::to_string((int)round(player->projectile_speed())) +
		"         Spd: " + std::to_string((int)round(player->speed())) +
		"         Rng: " + std::to_string((int)round(player->range()));// +
	//"                        Wave: " + std::to_string(wave->getWave()) +
	//"         Time: " + std::to_string(wave->getWaveDuration());
}

void HUD::render(Uint32, Assets*, SDL_Renderer* renderer, Configuration*, Scene*)
{
	
	Text hud_health(renderer, _health.c_str(), _hud_text_color, "HUD.Health");
	hud_health.render(renderer, Vector_2D(25.f, 25.f)); //render 
	
	/*
	Text hud_damage(renderer, _attackDamage.c_str(), _hud_text_color, "HUD.Attack.Damage");
	hud_damage.render(renderer, Vector_2D(25.f, 250.f));

	Text hud_attackSpeed(renderer, _attackSpeed.c_str(), _hud_text_color, "HUD.Attack.Speed");
	hud_attackSpeed.render(renderer, Vector_2D(25.f, 300.f));

	Text hud_projectileSpeed(renderer, _projectileSpeed.c_str(), _hud_text_color, "HUD.Projectile.Speed");
	hud_projectileSpeed.render(renderer, Vector_2D(25.f, 350.f));

	Text hud_speed(renderer, _speed.c_str(), _hud_text_color, "HUD.Speed");
	hud_speed.render(renderer, Vector_2D(25.f, 400.f));

	Text hud_range(renderer, _range.c_str(), _hud_text_color, "HUD.Range");
	hud_range.render(renderer, Vector_2D(25.f, 450.f));
	*/
}

/*
#include "hud.h"
#include "text.h"
#include "player.h"

HUD::HUD(std::string id)
	: Game_Object(id, "Texture.Player.Blank")
{
	_hud_text_color.r = 16;
	_hud_text_color.g = 16;
	_hud_text_color.b = 16;
	_hud_text_color.a = 255;
}

HUD::~HUD()
{
}

void HUD::simulate_AI(Uint32, Assets*, Input*, Scene* scene, SDL_Renderer*)
{
	Game_Object* player = scene->get_game_object("Player"); //get player

	_health = "HP: " + std::to_string(player->hp()); //set a string for the palyers health
	_attackDamage = "Dmg: " + std::to_string((int)player->attackDamage());
	_attackSpeed = "Atk Spd: " + std::to_string((int)player->attackSpeed());
	_projectileSpeed = "Proj Spd: " + std::to_string((int)player->projectile_speed());
	_speed = "Spd: " + std::to_string((int)player->speed());
	_range = "Rng: " + std::to_string((int)player->range());
}

void HUD::render(Uint32, Assets*, SDL_Renderer* renderer, Configuration*, Scene*)
{

	Text hud_health(renderer, _health.c_str(), _hud_text_color, "HUD.Health");
	hud_health.render(renderer, Vector_2D(25.f, 200.f)); //render

	Text hud_damage(renderer, _attackDamage.c_str(), _hud_text_color, "HUD.Attack.Damage");
	hud_damage.render(renderer, Vector_2D(25.f, 250.f));

	Text hud_attackSpeed(renderer, _attackSpeed.c_str(), _hud_text_color, "HUD.Attack.Speed");
	hud_attackSpeed.render(renderer, Vector_2D(25.f, 300.f));

	Text hud_projectileSpeed(renderer, _projectileSpeed.c_str(), _hud_text_color, "HUD.Projectile.Speed");
	hud_projectileSpeed.render(renderer, Vector_2D(25.f, 350.f));

	Text hud_speed(renderer, _speed.c_str(), _hud_text_color, "HUD.Speed");
	hud_speed.render(renderer, Vector_2D(25.f, 400.f));

	Text hud_range(renderer, _range.c_str(), _hud_text_color, "HUD.Range");
	hud_range.render(renderer, Vector_2D(25.f, 450.f));

}

*/