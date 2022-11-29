#include "Player.h"
#include "SDL.h"
#include "Game.h"

Player::Player(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames)
	: Character::Character(CharacterTexture, Pos, NumberOfFrames)
{
	Tag = "Player";
	MaxSpeed = 600;
}

Player::~Player()
{

}

void Player::Update(float DeltaTime)
{
	Character::Update(DeltaTime);


}

void Player::ProcessInput(Input* UserInput)
{
	float MovementX = 0.0f;
	float MovementY = 0.0f;
	float Speed = 2000.0f;

	// check if W key is down
	if (UserInput->IsKeyDown(SDL_SCANCODE_W)) {
		MovementY = -1.0f;
	}

	// check if S key is down
	if (UserInput->IsKeyDown(SDL_SCANCODE_S)) {
		MovementY = 1.0f;
	}
	
	// check if A key is down
	if (UserInput->IsKeyDown(SDL_SCANCODE_A)) {
		MovementX = -1.0f;
	}
	
	// check if D key is down
	if (UserInput->IsKeyDown(SDL_SCANCODE_D)) {
		MovementX = 1.0f;
	}

	AddForce(Speed, Vector2(MovementX, MovementY));

	// store the colliders overlapping out collider
	vector<Collider*> OtherColliders = GetCollisions()[0]->GetOverlappingColliders();

	if (UserInput->IsKeyDown(SDL_SCANCODE_SPACE)) {
		// run through all the colliders we're overlapping
		for (unsigned int i = 0; i < OtherColliders.size(); ++i) {
			if (OtherColliders[i]->GetOwner()->Tag == "Enemy") {
				// destroy enemy
				Game::GetGameInstance()->Score += 100;
				OtherColliders[i]->GetOwner()->DestroyGameObject();
			}
		}
	}

	// this will run through all the colliders overlapping each frame
	for (vector<Collider*>::iterator it = OtherColliders.begin(); it < OtherColliders.end(); ++it) {
		if ((*it)->GetOwner()->Tag == "Collectable") {
			(*it)->GetOwner()->DestroyGameObject();
		}
	}
}
