#pragma once
#include "GameState.h"
#include "Player.h"
#include "Text.h"
#include "SDL_mixer.h"

class PlayState :
    public GameState
{
public:
	PlayState();

	virtual void Update(float DeltaTime) override;
	virtual void Draw(SDL_Renderer* Renderer) override;
	virtual void ProcessInput(Input* UserInput) override { GameState::ProcessInput(UserInput); }

	virtual bool OnEnter(SDL_Renderer* Renderer, SDL_Window* Window) override;
	virtual bool OnExit() override;

protected:
	// store a pointer to the player game character
	Player* PChar;

	// store the text for the players position
	Text* TXT_PPosition;
	// read the score to the screen
	Text* TXT_Score;
	
	// background music
	Mix_Music* Music_BG;
};

