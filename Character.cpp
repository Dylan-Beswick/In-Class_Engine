#include "Character.h"
#include "SDL.h"
#include <iostream>
#include "Vector2.h"
#include "GameObject.h"

using namespace std;

Character::Character(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames)
{
	Position = Pos;
	ObjectCenter = Position;
	ObjectTexture = CharacterTexture;
	this->NumberOfFrames = NumberOfFrames;
	Velocity = Vector2().Zero();
	MovementAxis = Vector2().Zero();
	MaxSpeed = 100.0f;
	float w = 10.0f;
	float h = 10.0f;
	
	// if we have a texture then update the width and height based on the texture
	if (ObjectTexture != nullptr) {
		w = ObjectTexture->GetImageWidth() / SDL_max(1, NumberOfFrames);
		h = ObjectTexture->GetImageHeight();

		w /= 2;
		h /= 2;
	}

	SetCollision(ObjectCenter, Vector2(w, h));
}

void Character::Draw(SDL_Renderer* Renderer)
{
	GameObject::Draw(Renderer);

	SDL_Rect Clip;
	Clip.x = 0;
	Clip.y = 0;
	Clip.h = ObjectTexture->GetImageHeight();
	Clip.w = ObjectTexture->GetImageWidth() / SDL_max(1, NumberOfFrames);

	ObjectTexture->Draw(Renderer, Position, &Clip);
}

void Character::Update(float DeltaTime)
{
	// this will make sure the gameobject Update code runs first
	GameObject::Update(DeltaTime);

	// Set the velocity to be our movement axis normalised * our speed
	Velocity = MovementAxis.Normalised() * MaxSpeed;
	// move the character based on velocity
	Position += Velocity * DeltaTime;
}

void Character::SetMovementAxis(Vector2 Axis)
{
	MovementAxis = Axis;
}

Vector2 Character::GetMovementAxis()
{
	return MovementAxis;
}
