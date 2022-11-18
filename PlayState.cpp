#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"

PlayState::PlayState()
{
	DBColour = { 255, 0, 255, 255 };
}

bool PlayState::OnEnter(SDL_Renderer* Renderer)
{
	SDL_Log("Entered PlayState...");

	//initiallised the player texture
	Texture* PlayerTexture = new Texture();
	// load the player texture
	PlayerTexture->LoadImageFromFile("Assets/Hero-Spritesheet-50x37-109.png", Renderer);
	// construct the player as a character
	Player* PlayerCharacter = new Player(PlayerTexture, Vector2(0, 0), 109);
	GameObjectStack.push_back(PlayerCharacter);

	//initiallised the enemy texture
	Texture* EnemyTexture = new Texture();
	// load the enemy texture
	EnemyTexture->LoadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", Renderer);

	// construct the first enemy as an Enemy using the enemy texture
	Enemy* EnemyCharacter = new Enemy(EnemyTexture, Vector2(0, 37), 28);
	GameObjectStack.push_back(EnemyCharacter);

	//initiallised the enemy texture
	EnemyTexture = new Texture();
	// load the enemy texture
	EnemyTexture->LoadImageFromFile("Assets/goblin-spritesheet-65x35-28.png", Renderer);

	// construct the second enemy as an Enemy using the same enemy texture
	Enemy* EnemyCharacter2 = new Enemy(EnemyTexture, Vector2(0, 72), 28);
	GameObjectStack.push_back(EnemyCharacter2);

	return true;
}

bool PlayState::OnExit()
{
	SDL_Log("Exited PlayState...");

	return true;
}
