#pragma once

#include <Windows.h>
#include <string>

#include "input.h"
#include "Scene.h"
#include "configuration.h"

class Editor
{
public:
	Editor(std::wstring window_name);
	~Editor();

	void update(Input* input, Scene* scene, Configuration* config);

private:
	HWND _window;
	HMENU _menu;
};