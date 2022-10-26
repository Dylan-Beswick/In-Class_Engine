#pragma once
#include "SDL.h"

class Input
{
public:
	Input();
	~Input();

	void UpdateInput(bool &bIsGameOver);

	// these are to detect if a particular key is up or down
	bool IsKeyDown(SDL_Scancode Key);
	bool IsKeyUp(SDL_Scancode Key);

private:
	// store the state of each key
	const Uint8* KeyboardState;
};

