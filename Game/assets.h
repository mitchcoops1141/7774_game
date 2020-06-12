#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <string>
#include <map>

#include "texture.h"
#include "animated_texture.h"
#include "asset.h"

class Assets
{
public:
	Assets(SDL_Renderer* renderer);
	~Assets();

	Asset* get_asset(std::string id);
	void add_animated_asset(Animated_Texture* animated_texture);

private:
	std::map<std::string, Asset*> _assets;
};