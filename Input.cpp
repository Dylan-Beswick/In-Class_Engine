#include "Input.h"
#include "SDL_syswm.h"
#include "resource.h"
#include "Game.h"

Input::Input(Game* MyGame)
{
	KeyboardState = nullptr;
	this->MyGame = MyGame;
	// all SDL to detect menu input events
	SDL_EventState(SDL_SYSWMEVENT, SDL_ENABLE);
}

Input::~Input()
{
}

void Input::UpdateInput(bool &bIsGameOver, vector<SDL_Window*> SdlWindows)
{
	SDL_Event Event;
	while (SDL_PollEvent(&Event)) {
		// detect the type of input that was input
		switch (Event.type) {
		case SDL_KEYDOWN:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			KeyboardState = SDL_GetKeyboardState(NULL);
			break;
		case SDL_SYSWMEVENT:
			HandleMenuEvents(&Event, SdlWindows, bIsGameOver);
			break;
		default:
			break;
		}

		// when you hit the cross button on the app, close the game
		if (Event.window.event == SDL_WINDOWEVENT_CLOSE) {
			// if the main window close is pressed - end the game
			if (Event.window.windowID == SDL_GetWindowID(SdlWindows[0])) {
				bIsGameOver = true;
			}
			else {
				// if the secondary window close was pressed then hide the secondary window
				SDL_HideWindow(SdlWindows[1]);
			}
		}
	}
}

bool Input::IsKeyDown(SDL_Scancode Key)
{
	if (KeyboardState != nullptr && KeyboardState[Key] == true) {
		return true;
	}

	return false;
}

bool Input::IsKeyUp(SDL_Scancode Key)
{
	if (KeyboardState != nullptr && KeyboardState[Key] == true) {
		return false;
	}

	return true;
}

void Input::HandleMenuEvents(SDL_Event* Event, vector<SDL_Window*> SdlWindows, bool& bIsGameOver)
{
	// Detect a menu button was pressed
	switch (Event->syswm.msg->msg.win.wParam) {
	case ID_FILE_NEWWINDOW: // If we push the new window menu button
		SDL_ShowWindow(SdlWindows[1]); // show the secondary window
		break;
	case ID_FILE_EXIT: // if we push the exit game button
		bIsGameOver = true; // end the game/program
		break;
	case ID_SHAPES_RECTANGLE: 
		MyGame->AddRandomRectangle();
		break;
	case ID_SHAPES_RECTANGLEFILLED:
		MyGame->AddRandomRectangle(true);
		break;
	case ID_HELP_ABOUT: // if we push the about In-Class_Engine button
		// create a simple dialoge box that will display information then close when we push a button
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "About In-Class_Engine", "In-Class_Engine v0.8 is an SDL2 based game engine.", SdlWindows[0]);
		break;
	default:
		break;
	}
}
