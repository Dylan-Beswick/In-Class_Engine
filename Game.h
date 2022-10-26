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

using namespace std;


class Game
{
public:
	//constructor
	Game();
	//deconstructor
	~Game();

private:
	//the window that we will be rendering to
	SDL_Window* SdlWindow;
	//2D renderer
	SDL_Renderer* SdlRenderer;
	//flag for the game loop
	bool bIsGameOver;

	// Player texture
	Texture* PlayerTexture;
	// Enemy texture
	Texture* EnemyTexture;

	// initialise all Gameobjects
	vector<GameObject*> GameObjects;

	// all the colliders in the game will be stored here
	vector<Collider*> BoxColliders;

	Input* UserInput;

	// how long since last update
	unsigned int LastUpdateTime;

public:
	// Create the renderer
	// Allocate any objects we want
	bool Start();

	// Handle any inputs from the player that happens last call
	void ProcessInput();

	// Run on every tick - frame
	void Update();

	// Draw the game images to the screen
	void Draw();

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

