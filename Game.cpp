#include "Game.h"
#include <iostream>
using namespace std;

//Constructor
Game::Game()
{
	//Set the SDL Window and Renderer to null in case it has momory
	SdlWindow = nullptr;
	SdlRenderer = nullptr;

	//Initialise the subsystem in the SDL2 Framework
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {

		bIsGameOver = true;
		//if failed to initialise subsystem, tell us on the console
		cout << "Initialise SDL - failed" << endl;

	}
	else {

		//enable the game loop
		bIsGameOver = false;
		//if the subsystem sucesfully initialises
		cout << "Initialise SDL - sucess" << endl;

	}
}
//Deconstructor
Game::~Game()
{

}

bool Game::Start()
{
	// create the SDL renderer and define it
	SdlRenderer = SDL_CreateRenderer(SdlWindow, 0, -1);

	// make sure the renderer worked
	if (SdlRenderer != nullptr) {
		cout << "Create Renderer - success" << endl;

		// initialised the texture
		PlayerTexture = new Texture();
		// load the texture
		if (PlayerTexture->LoadImageFromFile("Assets/Mario.png", SdlRenderer)) {
			cout << "Player Texture - success" << endl;
		}
		else {
			cout << "Player Texture - failed" << endl;
			return false;
		}

		return true;
	}

	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	// @ TODO: Process player inputs
}

void Game::Update()
{
	//@ TODO: Add any changes to the game each frame

	// get how many seconds its been
	int Seconds = SDL_GetTicks() / 1000;

	// after 10 seconds kill the program
	if (Seconds > 9) {
		bIsGameOver = true;
	}
}

void Game::Draw()
{
	// set the draw colour
	SDL_SetRenderDrawColor(SdlRenderer, 128, 9, 217, 217);

	// clear the renderer
	SDL_RenderClear(SdlRenderer);

	//@ TODO: Draw stuff here
	PlayerTexture->Draw(SdlRenderer, 0, 0);

	SDL_RenderPresent(SdlRenderer);
}

void Game::Run(const char* title, int width, int height, bool fullscreen)
{
	// define the creation flag
	int CreationFlag = 0;

	// if fullscreen is set to false then set windowed mode
	if (!fullscreen) {
		CreationFlag = SDL_WINDOW_SHOWN;
	}
	else {
		CreationFlag = SDL_WINDOW_FULLSCREEN;
	}

	// create the SDL Window
	SdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		width, height, CreationFlag);

	// check if the SDL Window worked
	// create the renderer and start the game loop
	if (SdlWindow != nullptr && Start()) {
		cout << "Create Window - success" << endl;

		// run the game loop
		while (!bIsGameOver) {
			// check for player input
			ProcessInput();

			// process any changes that were made either by input or game code
			Update();

			// draw everything to the screen
			Draw();
		}
	}

	// debug if we failed or exited
	cout << "Create Window - failed or was exited" << endl;

	Shutdown();
	Destroy();
}

void Game::Shutdown()
{
	//@ TODO: deallocate all of the stuff we add in start
}

void Game::Destroy()
{
	// deallocate the window
	SDL_DestroyWindow(SdlWindow);

	// deallocate the renderer
	SDL_DestroyRenderer(SdlRenderer);

	// shut down the SDL Framework
	SDL_Quit();
}
