#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>

#include "asset.h"
#include "texture.h"


class Animated_Texture : public Texture
{
public:
	Animated_Texture(std::string id, std::string path, SDL_Renderer* renderer, int frame_count, Uint32 frame_duration_milliseconds, bool should_loop);
	~Animated_Texture();

	int get_frame_count();

	void set_frame_duration_milliseconds(Uint32 frame_duration_milliseconds);
	Uint32 get_frame_duration_milliseconds();

	void update_frame(Uint32 milliseconds_to_simulate);
	void reset();
	void render(SDL_Renderer* renderer, SDL_Rect* clip, SDL_Rect* destination, SDL_RendererFlip flip) override;

private:
	int      _frame_count;
	Uint32   _frame_duration_milliseconds;
	Uint32   _total_time_milliseconds;
	int      _current_frame;
	bool	 _should_loop;
};