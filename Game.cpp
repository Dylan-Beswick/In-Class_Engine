#include <iostream>
#include "Game.h"
#include "Character.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h"
#include "resource.h"
#include <Windows.h>
#include "SDL_syswm.h"
#include "RectangleObject.h"
#include <math.h>

using namespace std;

//Constructor
Game::Game()
{
	//Set the SDL Window and Renderer to null in case it has momory
	SdlWindow = { nullptr, nullptr };
	SdlRenderer = { nullptr, nullptr };
	LastUpdateTime = 0.0f;
	UserInput = nullptr;

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
	// clear the array gameobjects from memory
	vector<GameObject*>().swap(GameObjects);
	vector<GameObject*>().swap(SubGameObjects);
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

		//initiallised the player texture
		Texture* PlayerTexture = new Texture();
		// load the player texture
		PlayerTexture->LoadImageFromFile("Assets/Hero-Spritesheet-50x37-109.png", SdlRenderer[0]);
		// construct the player as a character
		Player* PlayerCharacter = new Player(PlayerTexture, Vector2(0, 0), 109);
		GameObjects.push_back(PlayerCharacter);

		//initiallised the enemy texture
		Texture* EnemyTexture = new Texture();
		// load the enemy texture
		EnemyTexture->LoadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", SdlRenderer[0]);
		
		// construct the first enemy as an Enemy using the enemy texture
		Enemy* EnemyCharacter = new Enemy(EnemyTexture, Vector2(0, 37), 28);
		GameObjects.push_back(EnemyCharacter);

		//initiallised the enemy texture
		EnemyTexture = new Texture();
		// load the enemy texture
		EnemyTexture->LoadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", SdlRenderer[0]);

		// construct the second enemy as an Enemy using the same enemy texture
		Enemy* EnemyCharacter2 = new Enemy(EnemyTexture, Vector2(0, 72), 28);
		GameObjects.push_back(EnemyCharacter2);

		return true;
	}

	cout << "Create Renderer - failed" << endl;

	return false;
}

void Game::ProcessInput()
{
	// @ TODO: Process player inputs
	UserInput->UpdateInput(bIsGameOver, SdlWindow);

	// cycle through all gameobjects and run their input
	for (unsigned int i = 0; i < GameObjects.size(); ++i) {
		GameObjects[i]->ProcessInput(UserInput);
	}
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

	// Clear the box colliders every frame
	BoxColliders.clear();

	// cycle through all gameobjects and run their update
	for (unsigned int i = 0; i < GameObjects.size(); ++i) {
		GameObjects[i]->Update(DeltaTime);

		// reassign or add box colliders based on gameobjects in the game
		if (GameObjects[i]->GetCollision() != nullptr) {
			BoxColliders.push_back(GameObjects[i]->GetCollision());
		}
	}

	// run the detection for the box colliders
	for (unsigned int i = 0; i < BoxColliders.size(); ++i) {
		BoxColliders[i]->Update(DeltaTime, BoxColliders);
	}
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

	// cycle through all gameobjects and run their draw
	for (unsigned int i = 0; i < GameObjects.size(); ++i) {
		GameObjects[i]->Draw(SdlRenderer[0]);
	}

	// cycle through all of the box colliders
	for (unsigned int i = 0; i < BoxColliders.size(); ++i) {
		BoxColliders[i]->Draw(SdlRenderer[0]);
	}

	// getting all the newly rendered stuff and showing it onto the window
	for (vector<SDL_Renderer*>::iterator it = SdlRenderer.begin(); it < SdlRenderer.end(); ++it) {
		SDL_RenderPresent(*it);
	}
}

void Game::HandleGarbage()
{
	// iterating through all of the gameobjects
	// create an interator (it) object that starts at the start of the gameobjects array
	// incrementing through the array and will delete game objects based on the iterator if it needs to
	for (vector<GameObject*>::iterator it = GameObjects.begin(); it < GameObjects.end(); ++it) {
		// if the gameobject is set to should delete
		// no need for the "== true", the statement passes true or false anyway
		if ((*it)->ShouldDelete()) {
			SDL_Log("GameObject Deleted...");
			// delete the specific gameobject iterator
			delete *it;
			// because we've deleted it we now need to remove it from the gameobjects array
			// since we have the iterator info in this foreach loop we can do that easily
			GameObjects.erase(it);
			// because we've erased the item from the iterator, we now need to stop the for loop
			// or we'll crash since the vector condition is now smaller than it's supposed to be
			// this is what out of scope means
			
			// break exits the for loop
			// it will no longer run anthing else in the for loop and just stop
			break;
		}
	}
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
