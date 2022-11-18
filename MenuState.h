#pragma once
#include "GameState.h"
class MenuState :
    public GameState
{
public:
	MenuState();

	virtual void Update(float DeltaTime) override { GameState::Update(DeltaTime); }
	virtual void Draw(SDL_Renderer* Renderer) override { GameState::Draw(Renderer); }
	virtual void ProcessInput(Input* UserInput) override { GameState::ProcessInput(UserInput); }

	virtual bool OnEnter(SDL_Renderer* Renderer) override;
	virtual bool OnExit() override;
};

