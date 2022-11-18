#include "MenuState.h"

MenuState::MenuState()
{
	DBColour = { 0, 0, 255, 255 };
}

bool MenuState::OnEnter(SDL_Renderer* Renderer)
{
	SDL_Log("MenuState Entered...");

	return true;
}

bool MenuState::OnExit()
{
	SDL_Log("Exited MenuState...");

	return true;
}
