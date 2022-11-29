#include "MSGameOver.h"
#include "Game.h"

bool MSGameOver::OnEnter(SDL_Renderer* Renderer, SDL_Window* Window)
{
	MenuState::OnEnter(Renderer, Window);

	string NewText = "Your Final Score Was " + to_string(Game::GetGameInstance()->Score);

	MenuTitle->ChangeText(NewText);

	return false;
}

void MSGameOver::ProcessInput(Input* UserInput)
{
	GameState::ProcessInput(UserInput);

	// go to the main menu screen
	if (UserInput->IsKeyDown(SDL_SCANCODE_RETURN)) {
		MenuState* NewState = new MenuState;
		Game::GetGameInstance()->ChangeGameState(NewState, 0);
	}
}
