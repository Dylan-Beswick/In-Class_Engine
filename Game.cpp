#include <iostream>
#include "Game.h"
#include "resource.h"
#include <Windows.h>
#include "SDL_syswm.h"
#include "RectangleObject.h"
#include <math.h>
#include "PlayState.h"
#include "MenuState.h"
#include "SDL_mixer.h"

using namespace std;

Game* Game::GetGameInstance()
{
	// if there is no game instance then make one
	if (GameInstance == nullptr) {
		GameInstance = new Game();
	}

	// return the game instance
	return GameInstance;
}

void Game::DestroyGameInstance()
{
	// check if there is a game instance
	if (GameInstance != nullptr) {
		delete GameInstance;
		GameInstance = nullptr;
	}
}

//Constructor
Game::Game()
{
	//Set the SDL Window and Renderer to null in case it has momory
	SdlWindow = { nullptr, nullptr };
	SdlRenderer = { nullptr, nullptr };
	LastUpdateTime = 0.0f;
	UserInput = nullptr;
	Score = 0;

	//Initialise the subsystem in the SDL2 Framework
	if (SDL_InitSubSystem(SDL_INIT_EVERYTHING) != 0) {

		bIsGameOver = true;
		//if failed to initialise subsystem, tell us on the console
		cout << "Initialise SDL - failed" << endl;

	}
	else {
		// Initialise our font library
		if (TTF_Init() == -1) {
			// if the font subsystem failed
			bIsGameOver = true;

			SDL_Log("Font subsystem - Failed");

			return;
		}

		// Initialise the Audio subsystem
		if (SDL_Init(SDL_INIT_AUDIO) != 0) {
			// end the game and log failure
			bIsGameOver = true;

			SDL_Log("Audio subsytem - Failed");

			return;
		}
		else {
			// activate the audio if successful

			// @param 1 - The audio device frequency, specified in Hz (Hertz); in modern time 48000 is reasonable as a default
			// @param 2 - The SDL audio format; SDL uses this to know what format to read the audio as;
			// @param 3 - Audio channels (1 - Mono or 2 - Stereo)
			// @param 4 - BitChunks; The latency the audio will send to the audio listener (Lower = Fastest; 1024 & 4096)
			Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096);
		}

		//enable the game loop
		bIsGameOver = false;
		//if the subsystem sucesfully initialises
		cout << "Initialise SDL - sucess" << endl;

	}
}
//Deconstructor
Game::~Game()
{
	vector<GameObject*>().swap(SubGameObjects);
}

void Game::ChangeGameState(GameState* NewState, Uint32 StateID)
{
	if (!GameStates.empty()) {
		// exit the game state
		GameStates.back()->OnExit();
		// delete the gamestate / mark as destroy for garbage collection
		GameStates.back()->DestroyGameState();
	}

	// create and assign the new game state
	NewState->StateID = StateID;
	GameStates.push_back(NewState);

	// this will make sure to run the on enter for all change game states
	GameStates.back()->OnEnter(SdlRenderer[0], SdlWindow[0]);
}

void Game::AddRandomRectangle(bool bFilled)
{
	// randomise all the variables of the rectangle
	// randomising the width and height but with a Min 10 and a Max 150
	float w = rand() % 150 + 10;
	float h = rand() % 150 + 10;
	// randomise the position but make sure that the center doesn't go outside the window
	float posx = rand() % 980;
	float posy = rand() % 540;

	// randomise the colour
	// we're using 256 because rand will ignore the last value and Max at 255
	SDL_Colour NewColour = { rand() % 256, rand() % 256, rand() % 256, rand() % 256 };

	// Create a rectangle using the above parameters
	RectangleObject* NewRectangle = new RectangleObject(w, h, Vector2(posx, posy), NewColour, bFilled);
	SubGameObjects.push_back(NewRectangle);
}

bool Game::Start()
{
	// create the SDL renderer and define it
	// assigning the correct renderer to the correct window
	SdlRenderer[0] = SDL_CreateRenderer(SdlWindow[0], 0, -1);
	// creating the second rederer
	SdlRenderer[1] = SDL_CreateRenderer(SdlWindow[1], 0, -1);

	// get the start time of the clock in milliseconds
	LastUpdateTime = SDL_GetTicks();

	// make sure the renderer worked
	if (SdlRenderer[0] != nullptr && SdlRenderer[1] != nullptr) {
		cout << "Create Renderer - success" << endl;

		// Start Detecting Input
		UserInput = new Input(this);

		// creating a starter game state
		MenuState* StarterGameState = new MenuState();
		ChangeGameState(StarterGameState, 0);

		return true;
	}

	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	// @ TODO: Process player inputs
	UserInput->UpdateInput(bIsGameOver, SdlWindow);

	// run the gamestate process input
	GameStates.back()->ProcessInput(UserInput);
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

	/*
	// 1000ms per second
	if (SDL_GetTicks() > 5000) {
		if (GameStates.back()->StateID == 0) {
			// telling the state it's exited
			GameStates.back()->OnExit();
			// deallocate the state from memory
			delete GameStates.back();
			// reduce the size of the vector
			GameStates.pop_back();

			// create a new play state
			PlayState* NewPlayState = new PlayState();
			// change the ID so this if condition doesn't run again
			NewPlayState->StateID = 1;
			// Tell the GameState its stated
			NewPlayState->OnEnter(SdlRenderer[0], SdlWindow[0]);
			// add it to the GameState Stack
			GameStates.push_back(NewPlayState);
		}
	}*/

	// run the gamestate update
	GameStates.back()->Update(DeltaTime);
}

void Game::Draw()
{
	// set the draw colour
	SDL_SetRenderDrawColor(SdlRenderer[0], 128, 9, 217, 255);
	// set background colour of second window
	SDL_SetRenderDrawColor(SdlRenderer[1], 255, 0, 0, 255);

	// clear the renderers
	for (vector<SDL_Renderer*>::iterator it = SdlRenderer.begin(); it < SdlRenderer.end(); ++it) {
		SDL_RenderClear(*it);
	}

	//@ TODO: Draw stuff here

	// Draw Secondary Objects to the secondary renderer
	for (vector<GameObject*>::iterator it = SubGameObjects.begin(); it < SubGameObjects.end(); ++it) {
		(*it)->Draw(SdlRenderer[1]);
	}

	// run the draw in our gamestate
	GameStates.back()->Draw(SdlRenderer[0]);

	// getting all the newly rendered stuff and showing it onto the window
	for (vector<SDL_Renderer*>::iterator it = SdlRenderer.begin(); it < SdlRenderer.end(); ++it) {
		SDL_RenderPresent(*it);
	}
}

void Game::HandleGarbage()
{
	// run through all game states and check if they need to be deleted
	for (vector<GameState*>::iterator State = GameStates.begin(); State < GameStates.end();) {
		if ((*State)->ShouldDelete()) {
			delete* State;
			State = GameStates.erase(State);
			continue;
		}

		// Increment the iterator if we didn't delete the state
		State++;
	}

	// run the gamestate Handle Garbage
	GameStates.back()->HandleGarbage();
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
	SdlWindow[0] = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		width, height, CreationFlag);
	// create the second SDL Window
	SdlWindow[1] = SDL_CreateWindow("In-Class_Engine Secondary Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
		800, 600, SDL_WINDOW_HIDDEN);

	// check if the SDL Window worked
	// create the renderer and start the game loop
	if (SdlWindow[0] != nullptr && SdlWindow[1] != nullptr && Start()) {
		cout << "Create Window - success" << endl;

		// get the window information for the system that we can use to add the menu to
		SDL_SysWMinfo WindowInfo;
		// get the version of SDL we are using and add it into the WindowInfo
		SDL_VERSION(&WindowInfo.version);
		// we then assign the rest of the information about the sdlwindow into the variable
		SDL_GetWindowWMInfo(SdlWindow[0], &WindowInfo);

		// We're gonna convert our SDL window into a windows window and store it
		HWND hWindow = WindowInfo.info.win.window;
		// We need to get the menu from our resources header
		// GetModuleHandle() return the name of the program that we are currently running
		// MAKEINTRESOURCE() convert the ID of the menu into the required format LPCWSTR
		HMENU hMenu = LoadMenu(GetModuleHandle(0), MAKEINTRESOURCE(IDR_MENU1));

		SetMenu(hWindow, hMenu);

		// run the game loop
		while (!bIsGameOver) {
			// delete gameobjects that are marked for delete
			HandleGarbage();

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
	SDL_DestroyWindow(SdlWindow[0]);
	SDL_DestroyWindow(SdlWindow[1]);

	// deallocate the renderer
	SDL_DestroyRenderer(SdlRenderer[0]);
	SDL_DestroyRenderer(SdlRenderer[1]);

	// shut down the SDL Framework
	SDL_Quit();
}
