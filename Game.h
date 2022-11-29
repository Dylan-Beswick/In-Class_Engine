#pragma once

//setup SDL
#include <SDL.h>
#include "Texture.h"
#include "Animation.h"
#include "GameObject.h"
#include "Character.h"
#include <iostream>
#include <vector>
#include "Input.h"
#include "Collider.h"
#include "GameState.h"

using namespace std;

// this holds a reference to the memory of the game instance
// this will only ever have one class assigned per game start
static Game* GameInstance;

class Game
{
public:
	// if there is no game instance this will create one then return it
	// if there already is a game instance this will just return the current one
	static Game* GetGameInstance();

	// since we dont have public access to the destructor we need to delete the class in a static function
	static void DestroyGameInstance();

	// score that remains over states
	int Score;

private:
	// these need to be private so we can't create non-instance versions of the game instance
	//constructor
	Game();
	//destructor
	~Game();

	//the window that we will be rendering to
	// with vectors we can now store more than 1 window and renderer
	vector<SDL_Window*> SdlWindow;
	//2D renderer
	vector<SDL_Renderer*> SdlRenderer;
	//flag for the game loop
	bool bIsGameOver;

	// this will store our current gamestate
	vector<GameState*> GameStates;

	// initialise all of the sub window game objects
	vector<GameObject*> SubGameObjects;

	Input* UserInput;

	// how long since last update
	unsigned int LastUpdateTime;

public:
	// this will change the game state
	void ChangeGameState(GameState* NewState, Uint32 StateID);

	// Add a random rectangle to the secondary window
	void AddRandomRectangle(bool bFilled = false);

	// Create the renderer
	// Allocate any objects we want
	bool Start();

	// Handle any inputs from the player that happens last call
	void ProcessInput();

	// Run on every tick - frame
	void Update();

	// Draw the game images to the screen
	void Draw();

	// run a function that will handle deleting objects BEFORE or AFTER all functionality is complete
	void HandleGarbage();

	// This will create the window and begin the game loop
	//@param 1 - title of the window
	//@param 2 - width of the window
	//@param 3 - height of the window
	//@param 4 - whether or not we fullscreen
	void Run(const char* title, int width, int height, bool fullscreen);

	// Deallocate objects from memory
	void Shutdown();

	// Shutdown the SDL Framework, delete the renderer from memory
	void Destroy();

};

