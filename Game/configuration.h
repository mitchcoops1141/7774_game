#pragma once

struct Configuration
{
	bool should_display_ids = false;

	bool should_display_colliders = false;

	bool hardMode = false; //hard mode 2 stat upgrade per wave and 3 HP. easy mode 3 stat upgrades per wave and 5 HP.

	int window_width = 800;
	int window_height = 800;
};