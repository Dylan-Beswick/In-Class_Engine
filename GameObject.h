#pragma once
#include "SDL.h"
#include "Texture.h"
#include "Vector2.h"
#include "Input.h"
#include "Collider.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void Draw(SDL_Renderer* Renderer);
	virtual void Update(float DeltaTime);
	virtual void ProcessInput(Input* UserInput);

	// this is going to create a collision for the game object
	void SetCollision(Vector2 Position = Vector2().Zero(), Vector2 HalfDimensions = Vector2(1.0f, 1.0f), bool ShouldDebug = true);

	// this will change the width and height of the collider
	void SetCollisionDimensions(Collider* Collision, Vector2 HalfDimensions);

	// this will move the position of the collision based on the objects center
	void UpdateCollisionPosition();
	void FindObjectCenter();

	// Get the collision publically
	Collider* GetCollision();

protected:
	// positions for the game object to display on the window
	Vector2 Position;
	// The objects texture
	Texture* ObjectTexture;
	// Collider
	Collider* Collision;
	// get the center of the object
	Vector2 ObjectCenter;
	// Number of frames in the object texture
	unsigned int NumberOfFrames;
	
};

