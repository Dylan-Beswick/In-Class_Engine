#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char** argv) {

	// create the game class and allocate it to memory
	Game* NewGame = new Game();

	// run the game
	NewGame->Run("In-Class_Engine", 1280, 720, false);

	// deallocate the game object
	delete NewGame;

	return 0;
}