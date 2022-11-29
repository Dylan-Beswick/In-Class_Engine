#pragma once
#include "GameState.h"
#include "Text.h"
#include "SDL_mixer.h"

class MenuState :
    public GameState
{
public:
	MenuState();

	virtual void Update(float DeltaTime) override { GameState::Update(DeltaTime); }
	virtual void Draw(SDL_Renderer* Renderer) override;
	virtual void ProcessInput(Input* UserInput) override;

	virtual bool OnEnter(SDL_Renderer* Renderer, SDL_Window* Window) override;
	virtual bool OnExit() override;

protected:
	Text* MenuTitle;
	Mix_Chunk* SFX_Enter;
};

