#include "assets.h"
#include "texture.h"
#include "animated_texture.h"
#include "sound.h"
#include "text.h"

#include <iostream>

Assets::Assets(SDL_Renderer* renderer)
{
	//CACHE:
	//player blank frame
	{
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Blank",
			"Assets/player.blank.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player death
	{
		const int frame_count = 19;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Death",
			"Assets/player.death.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			false);
		_assets[texture->id()] = texture;
	}

	//player legs idle
	{
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Legs.Idle",
			"Assets/player.legs.idle.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player legs walk right
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Legs.Walk.Right",
			"Assets/player.legs.walk.right.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player legs walk left
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Legs.Walk.Left",
			"Assets/player.legs.walk.left.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player legs walk up
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Legs.Walk.Up",
			"Assets/player.legs.walk.up.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player legs walk down
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Legs.Walk.Down",
			"Assets/player.legs.walk.down.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player body idle
	{
		const int frame_count = 32;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Idle",
			"Assets/player.body.idle.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player body attack up
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 50;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Attack.Up",
			"Assets/player.body.attack.up.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			false);
		_assets[texture->id()] = texture;
	}

	//player body attack down
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 50;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Attack.Down",
			"Assets/player.body.attack.down.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			false);
		_assets[texture->id()] = texture;
	}

	//player body attack left
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 50;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Attack.Left",
			"Assets/player.body.attack.left.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			false);
		_assets[texture->id()] = texture;
	}

	//player body attack right
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 50;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Attack.Right",
			"Assets/player.body.attack.right.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			false);
		_assets[texture->id()] = texture;
	}

	//player body walk up
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Walk.Up",
			"Assets/player.body.walk.up.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player body walk down
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Walk.Down",
			"Assets/player.body.walk.down.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player body walk right
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Walk.Right",
			"Assets/player.body.walk.right.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//player body walk left
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Player.Body.Walk.Left",
			"Assets/player.body.walk.left.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//paper ball
	{
		const int frame_count = 8;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Paper.Ball",
			"Assets/paper.ball.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//collider texture
	{
		Texture* texture = new Texture("Texture.Collider", "Assets/collider.png", renderer);
		_assets[texture->id()] = texture;
	}

	//background texture
	{
		Texture* texture = new Texture("Texture.Background", "Assets/background.png", renderer);
		_assets[texture->id()] = texture;
	}

	//music sound
	{
		Sound* sound = new Sound("Sound.Music", "Assets/music.wav");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
		Mix_Volume(0, MIX_MAX_VOLUME/4);
	}

	//walking sound effect
	{
		Sound* sound = new Sound("Sound.Player.Walking", "Assets/walking.wav");
		_assets[sound->id()] = sound;

		//Mix_PlayChannel(1, sound->data(), -1);
	}

	//player death sound
	{
		Sound* sound = new Sound("Sound.Player.Death", "Assets/player.death.wav");
		_assets[sound->id()] = sound;
	}

	//menu text
	{
		Texture* texture = new Texture("Texture.Menu", "Assets/Menu.png", renderer);
		_assets[texture->id()] = texture;
	}

	//menu start selected text
	{
		Texture* texture = new Texture("Texture.Menu.Start", "Assets/menu.start.selected.png", renderer);
		_assets[texture->id()] = texture;
	}

	//menu settings selceted text
	{
		Texture* texture = new Texture("Texture.Menu.Settings", "Assets/menu.settings.selected.png", renderer);
		_assets[texture->id()] = texture;
	}

	//menu exit selected text
	{
		Texture* texture = new Texture("Texture.Menu.Exit", "Assets/menu.exit.selected.png", renderer);
		_assets[texture->id()] = texture;
	}

	//Enemy walk down
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Enemy.Walk.Down",
			"Assets/enemy.walk.down.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//Enemy walk up
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Enemy.Walk.Up",
			"Assets/enemy.walk.up.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//Enemy walk left
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Enemy.Walk.Left",
			"Assets/enemy.walk.left.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//Enemy walk right
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 150;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Enemy.Walk.Right",
			"Assets/enemy.walk.right.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//Enemy Agro Down
	{
		const int frame_count = 4;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Enemy.Agro.Down",
			"Assets/enemy.agro.down.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}

	//shield
	{
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Animated_Texture* texture = new Animated_Texture(
			"Texture.Shield",
			"Assets/shield.png",
			renderer,
			frame_count,
			frame_duration_milliseconds,
			true);
		_assets[texture->id()] = texture;
	}


}

Assets::~Assets()
{

}

Asset* Assets::get_asset(std::string id)
{
	if (_assets.find(id) == _assets.end())
	{
		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}

	return _assets[id];
}