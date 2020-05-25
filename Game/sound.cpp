#include "sound.h"
#include <iostream>

Sound::Sound(std::string id, std::string path)
	: Asset(id)
{
	_data = Mix_LoadWAV(path.c_str());

	if (_data == nullptr)
	{
		std::cout << "Failed to load the WAV. Path: " << path << std::endl;
		std::cout << "Mixer Error: " << Mix_GetError();
		exit(1);
	}
}

Mix_Chunk* Sound::data()
{
	return _data;
}
