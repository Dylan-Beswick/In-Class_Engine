#include "GameObject.h"
#include "Vector2.h"
#include "SDL.h"
#include "Collider.h"

GameObject::GameObject()
{
	Position = Vector2().Zero();
	ObjectTexture = nullptr;
	ObjectCenter = Position;
	NumberOfFrames = 1;
	bShouldDelete = false;
	Tag = "";
}

GameObject::~GameObject()
{
	// remove the collision from memory if there is one
	for (vector<Collider*>::iterator Col = Collisions.begin(); Col < Collisions.end(); Col++) {
		delete *Col;
	}

	// shrink the array to a 0 size vector
	vector<Collider*>().swap(Collisions);

	// remove the texture from memory if there is one
	if (ObjectTexture != nullptr) {
		SDL_Log("Delete Object Texture...");
		delete ObjectTexture;
		ObjectTexture = nullptr;
	}
}

void GameObject::UpdateGameObject(float DeltaTime, vector<GameObject*>& GameObjectStack)
{
	// this will find the object center based on the texture if there is one
	FindObjectCenter();
	// this will update the collision position to match the object center
	UpdateCollisionPosition();

	// Creater a temporary vector of all colliders
	vector<Collider*> OtherColliders = {};

	// search through all the gameobjects to get their colliders
	for (vector<GameObject*>::iterator GO = GameObjectStack.begin(); GO < GameObjectStack.end(); GO++) {
		// point to the vector of colliders in each gameobject
		vector<Collider*> GOColliders = (*GO)->GetCollisions();
		// loop through the gameobject colliders and add them each into the OtherColliders vector
		for (vector<Collider*>::iterator Col = GOColliders.begin(); Col < GOColliders.end(); Col++) {
			// add the collider to the vector
			OtherColliders.push_back(*Col);
		}
	}

	// handle the collision detection for out colliders
	for (vector<Collider*>::iterator Col = OtherColliders.begin(); Col < OtherColliders.end(); Col++) {
		(*Col)->Update(DeltaTime, OtherColliders);
	}

	// run the derived Update
	Update(DeltaTime);
}

void GameObject::Draw(SDL_Renderer* Renderer)
{
	// check through the colliders if we have any
	for (vector<Collider*>::iterator Col = Collisions.begin(); Col < Collisions.end(); Col++) {
		// run the draw if they have debug set
		if ((*Col)->bDebug) {
			// draw each collider
			(*Col)->Draw(Renderer);
		}
	}
}

void GameObject::SetCollision(Vector2 Position, Vector2 HalfDimensions, bool ShouldDebug)
{
	// define the gameobjects collision
	Collider* NewCollision = new Collider(this, Position, HalfDimensions, ShouldDebug);
	// add the collider to the collision vector
	Collisions.push_back(NewCollision);
}

void GameObject::SetCollisionDimensions(Collider* Collision, Vector2 HalfDimensions)
{
	if (Collision != nullptr) {
		// set the width of the collider
		Collision->ColliderRect.w = HalfDimensions.x * 2;
		// set the height of the collider
		Collision->ColliderRect.h = HalfDimensions.y * 2;
	}
}

void GameObject::UpdateCollisionPosition()
{
	// check if there is even a collision
	for (vector<Collider*>::iterator Col = Collisions.begin(); Col < Collisions.end(); Col++) {
		float w = (*Col)->ColliderRect.w / 2;
		float h = (*Col)->ColliderRect.h / 2;

		// Change the position of the collider to equal the object center
		// center the collider based on it's half dimensions
		(*Col)->ColliderRect.x = ObjectCenter.x - w;
		(*Col)->ColliderRect.y = ObjectCenter.y - h;
	}
}

void GameObject::FindObjectCenter()
{
	// make sure we set back to the position each frame
	ObjectCenter = Position;

	if (ObjectTexture != nullptr) {
		float w = ObjectTexture->GetImageWidth() / SDL_max(1, NumberOfFrames);
		float h = ObjectTexture->GetImageHeight();

		// w = w / 2;
		w /= 2;
		h /= 2;

		// ObjectCenter = ObjectCenter + w;
		ObjectCenter.x += w;
		ObjectCenter.y += h;
	}
}

vector<Collider*> GameObject::GetCollisions()
{
	// return a vector of Collisions
	return Collisions;
}

bool GameObject::ShouldDelete() const
{
	// this will be the key that tells the game this needs to be deleted
	return bShouldDelete;
}

void GameObject::DestroyGameObject()
{
	// set should delete
	bShouldDelete = true;
}
