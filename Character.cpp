#include "Character.h"
#include "SDL.h"
#include "GameObject.h"

Character::Character(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames)
{
	Position = Pos;
	ObjectCenter = Position;
	ObjectTexture = CharacterTexture;
	this->NumberOfFrames = NumberOfFrames;
	Velocity = Vector2().Zero();
	MovementAxis = Vector2().Zero();
	float w = 10.0f;
	float h = 10.0f;

	// if we have a texture then update the width and height based on the texture
	if (ObjectTexture != nullptr) {
		float w = ObjectTexture->GetImageWidth() / SDL_max(1, NumberOfFrames);
		float h = ObjectTexture->GetImageHeight();

		w /= 2;
		h /= 2;
	}
}

Character::~Character()
{
}

void Character::Update(float DeltaTime)
{

	GameObject::Update(DeltaTime)
}
