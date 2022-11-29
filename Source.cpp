#include <iostream>
#include "Game.h"
using namespace std;

int main(int argc, char** argv) {

	// run the game
	Game::GetGameInstance()->Run("In-Class_Engine", 980, 540, false);

	// deallocate the game object
	Game::DestroyGameInstance();

	return 0;
}