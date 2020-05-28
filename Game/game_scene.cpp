#include "game_scene.h"

#include "player.h"
#include "player_body.h"
#include "player_legs.h"
#include "background.h"
#include "paper_ball.h"
#include "enemy.h"
#include "text.h"
#include "hud.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	add_game_object(new Background("Background"));
	add_game_object(new HUD("HUD"));
	add_game_object(new Player("Player"));
	add_game_object(new Player_Legs("Player.Legs"));
	add_game_object(new Player_Body("Player.Body"));
	add_game_object(new Enemy("Enemy1", Vector_2D(1700, 200)));	
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window* window)
{
	_background_color.r = 70;
	_background_color.g = 130;
	_background_color.b = 60;

	Game_Object* player = get_game_object("Player");
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	_camera_translation = Vector_2D(-w / 2.f + player->width() / 2, -h / 2.f + player->height() / 2.f) + player->translation();

	//lock camera to the screen
	if (_camera_translation.x() < 0)
	{
		_camera_translation = Vector_2D(0, _camera_translation.y());
	}
	if (_camera_translation.x() > 1920)
	{
		_camera_translation = Vector_2D(1920, _camera_translation.y());
	}
	if (_camera_translation.y() < 0)
	{
		_camera_translation = Vector_2D(_camera_translation.x(), 0);
	}
	if (_camera_translation.y() > 1080)
	{
		_camera_translation = Vector_2D(_camera_translation.x(), 1080);
	}
}