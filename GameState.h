#pragma once
#include "SDL.h"
#include "Input.h"
#include "GameObject.h"

class GameState
{
public:
	GameState();
	~GameState();

	// the gamestates version of all of the loop functions
	virtual void Update(float DeltaTime);
	virtual void Draw(SDL_Renderer* Renderer);
	virtual void ProcessInput(Input* UserInput);
	virtual void HandleGarbage();

	// will be called when the gamestate begins and ends
	virtual bool OnEnter(SDL_Renderer* Renderer) { return true; }
	virtual bool OnExit() { return true; }

	// way to identify the state
	Uint32 StateID;
	
	// the default background colour of the state
	SDL_Colour DBColour;

protected:
	// this will store all the gameobjects in the state
	vector<GameObject*> GameObjectStack;
};

