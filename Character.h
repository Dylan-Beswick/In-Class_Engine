#pragma once
#include "GameObject.h"
#include "SDL.h"
#include "Vector2.h"

class Character :
	public GameObject
{
public:
	Character(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames = 1);
	~Character() {}

	void Draw(SDL_Renderer* Renderer) override;
	virtual void Update(float DeltaTime) override;
	virtual void ProcessInput(Input* UserInput) override {}

	// this will add force to the character based on the force provided and max speed
	void AddForce(float Force, Vector2 Direction);

protected:
	float MaxSpeed;

	void SetMovementAxis(Vector2 Axis);
	Vector2 GetMovementAxis();

	// should slow down the velocity of the player over time
	// set between 0 and 1
	float Drag;

private:
	// Velocity is the true representation of speed, this will have an x and y value
	Vector2 Velocity;
	// This is going to detect input and move out character based on it's direction
	// make sure the number is normally between 0 and 1
	Vector2 MovementAxis;
	// This will accelerate our velocity using force
	Vector2 Acceleration;
};

