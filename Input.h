#pragma once
#include "SDL.h"
#include <vector>

using namespace std;

// forward declare game to avoid circular dependencies
class Game;

class Input
{
public:
	Input(Game* MyGame);
	~Input();

	void UpdateInput(bool &bIsGameOver, vector<SDL_Window*> SdlWindows);

	// these are to detect if a particular key is up or down
	bool IsKeyDown(SDL_Scancode Key);
	bool IsKeyUp(SDL_Scancode Key);
	
protected:
	void HandleMenuEvents(SDL_Event* Event, vector<SDL_Window*> SdlWindows, bool &bIsGameOver);

private:
	// store the state of each key
	const Uint8* KeyboardState;
	// store the game class
	Game* MyGame;
};

