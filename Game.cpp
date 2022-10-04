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

	LastUpdateTime = SDL_GetTicks();

	// make sure the renderer worked
	if (SdlRenderer != nullptr) {
		cout << "Create Renderer - success" << endl;

		// initialised the texture
		PlayerTexture = new Texture();
		// load the texture
		if (PlayerTexture->LoadImageFromFile("Assets/Hero-Spritesheet-50x37-109.png", 
			SdlRenderer)) {
			cout << "Player Texture - success" << endl;

			// initialize player animations
			PlayerAnim.AirAttack = new Animation(PlayerTexture, 109, 0.1f, 0, 10);
			PlayerAnim.Idle = new Animation(PlayerTexture, 109, 0.1f, 60, 62);
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

	// how long since the last frame was updated in milliseconds
	unsigned int tick = SDL_GetTicks() - LastUpdateTime;

	// change the tick to seconds
	float DeltaTime = tick / 1000.0f;

	// Refresh the last update time
	LastUpdateTime = SDL_GetTicks();

	//@TODO add anything that needs DeltaTime below here
	PlayerAnim.AirAttack->Update(DeltaTime);
	PlayerAnim.Idle->Update(DeltaTime);

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
	PlayerAnim.AirAttack->Draw(SdlRenderer, 50, 50, 5);
	PlayerAnim.Idle->Draw(SdlRenderer, 300, 50, 5, true);

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
	SdlWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, width, height, CreationFlag);

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
