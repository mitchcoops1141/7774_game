#include "texture.h"

#include <SDL_image.h>

#include <iostream>

Texture::Texture(std::string id, std::string path, SDL_Renderer* renderer)
	: Asset(id)
{
	SDL_Surface* surface = nullptr; //create surface
	//if using bmp
	if(path.find("bmp") != std::string::npos)
	{
		surface = SDL_LoadBMP(path.c_str()); //load bmp
	}
	//if using png
	else if(path.find("png") != std::string::npos)
	{
		surface = IMG_Load(path.c_str()); //load png
	}
	//error code
	else
	{
		std::cout << "Unknown image file extension. Path: " << path << std::endl; //error 
		exit(1);
	}

	if(surface == nullptr) //error code
	{
		std::cout << "Failed to load image. Path: " << path << std::endl; //error
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_data = SDL_CreateTextureFromSurface(renderer, surface); //create texture
	if(_data == nullptr) //error code
	{
		std::cout << "Failed to create texture. Path: " << path << std::endl; //error
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	SDL_FreeSurface(surface); //free the surface
}

Texture::~Texture()
{
	SDL_DestroyTexture(_data); //destroy the texture
}
SDL_Texture* Texture::data()
{
	return _data; //get data
}

void Texture::render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip)
{
	const int render_result = SDL_RenderCopyEx(renderer, _data, clip, destination, 0, nullptr, flip);
	const int render_success = 0;
	if (render_result != render_success)
	{
		std::cout << "Failed to render texture" << std::endl;
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		exit(1);
	}
}