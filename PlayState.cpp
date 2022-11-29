#include "PlayState.h"
#include "Player.h"
#include "Enemy.h"
#include "EndGoalObject.h"
#include <string>
#include "Game.h"

PlayState::PlayState()
{
	DBColour = { 255, 0, 255, 255 };
	TXT_PPosition = nullptr;
	PChar = nullptr;
	Music_BG = nullptr;
	TXT_Score = nullptr;
}

void PlayState::Update(float DeltaTime)
{
	GameState::Update(DeltaTime);

	// make sure the text and the player character exist
	if (PChar != nullptr && TXT_PPosition != nullptr) {
		// initialise some integers to use for concatenation
		// use integers so that we don't display decimals
		int x, y = 0;

		// set the x and y to the players position
		// convert the floats into ingegers
		x = static_cast<int>(PChar->GetPosition().x);
		y = static_cast<int>(PChar->GetPosition().y);

		// form and concatenate the string
		string NewText = "X: " + to_string(x) + ", Y: " + to_string(y);

		// run the new text
		TXT_PPosition->ChangeText(NewText);

	}

	if (TXT_Score != nullptr) {
		int score = Game::GetGameInstance()->Score;

		string NewText = "Score: " + to_string(score);

		TXT_Score->ChangeText(NewText);
	}
}

void PlayState::Draw(SDL_Renderer* Renderer)
{
	GameState::Draw(Renderer);

	if (TXT_PPosition != nullptr) {
		TXT_PPosition->Draw(Renderer);
	}

	if (TXT_Score != nullptr) {
		TXT_Score->Draw(Renderer);
	}
}

bool PlayState::OnEnter(SDL_Renderer* Renderer, SDL_Window* Window)
{
	SDL_Log("Entered PlayState...");

	//initiallised the player texture
	Texture* PlayerTexture = new Texture();
	// load the player texture
	PlayerTexture->LoadImageFromFile("Assets/Hero-Spritesheet-50x37-109.png", Renderer);
	// construct the player as a character
	PChar = new Player(PlayerTexture, Vector2(0, 0), 109);
	GameObjectStack.push_back(PChar);

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

	EndGoalObject* EndGoal = new EndGoalObject(Vector2(300.0f, 300.0f), Vector2(25.0f, 25.0f));
	GameObjectStack.push_back(EndGoal);

	// this will create the position text
	TXT_PPosition = new Text;
	SDL_Colour TextColour = { 255, 255, 255, 255 };
	if (!TXT_PPosition->InitialiseFont(Renderer, "Assets/VT323-Regular.ttf", 24,
		"X: 0, Y:0", TextColour, Vector2(15.0f, 15.0f))) {
		delete TXT_PPosition;
		TXT_PPosition = nullptr;
	}
	TXT_Score = new Text;
	if (!TXT_Score->InitialiseFont(Renderer, "Assets/VT323-Regular.ttf", 24,
		"Score: 0", TextColour, Vector2(15.0f, 45.0f))) {
		delete TXT_Score;
		TXT_Score = nullptr;
	}

	// find the music and load it
	Music_BG = Mix_LoadMUS("Assets/BackgoundMusic.wav");

	// play the music
	if (Music_BG != nullptr) {
		Mix_PlayMusic(Music_BG, -1);
	}

	return true;
}

bool PlayState::OnExit()
{
	SDL_Log("Exited PlayState...");

	if (PChar != nullptr) {
		PChar = nullptr;
	}

	// deallocate the text
	if (TXT_PPosition != nullptr) {
		delete TXT_PPosition;
		TXT_PPosition = nullptr;
	}
	// deallocate the score text
	if (TXT_Score != nullptr) {
		delete TXT_Score;
		TXT_Score = nullptr;
	}

	if (Music_BG != nullptr) {
		Mix_FreeMusic(Music_BG);
		Music_BG = nullptr;

	}

	return true;
}
