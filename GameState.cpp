#include "GameState.h"

GameState::GameState()
{
	StateID = 0;
	DBColour = { 15, 15, 15, 255 };
}

GameState::~GameState()
{
	// deallocate all of the game objects in the state
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end(); GO++) {
		delete* GO;
	}

	// clear the vector
	vector<GameObject*>().swap(GameObjectStack);
}

void GameState::Update(float DeltaTime)
{
	// loop through all of the gameobjects and run their update
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end(); GO++) {
		(*GO)->UpdateGameObject(DeltaTime, GameObjectStack);
	}
}

void GameState::Draw(SDL_Renderer* Renderer)
{
	// Draw background colour as blue
	SDL_SetRenderDrawColor(Renderer, DBColour.r, DBColour.g, DBColour.b, DBColour.a);
	SDL_RenderClear(Renderer);

	// loop through all of the game objects and run their draw
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end(); GO++) {
		(*GO)->Draw(Renderer);
	}
}

void GameState::ProcessInput(Input* UserInput)
{
	// loop through all of the game objects and run their processinput
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end(); GO++) {
		(*GO)->ProcessInput(UserInput);
	}
}

void GameState::HandleGarbage()
{
	// loop through all of the game objects and handle their garbage
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end();) {
		// check if they are marked for delet
		if ((*GO)->ShouldDelete()) {
			// deallovate it from memory
			delete* GO;
			// assign a new iterator that solves for the erased item
			GO = GameObjectStack.erase(GO);
		}
		else {
			// increment the iterator if we didn't delete anything
			GO++;
		}
	}
}
