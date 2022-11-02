#include "Collider.h"
#include <vector>

using namespace std;

Collider::Collider(GameObject* OwnerObject, Vector2 Position, Vector2 HalfDimensions, bool ShouldDebug)
{
	bDebug = ShouldDebug;
	OverlappedColliders = {};
	this->OwnerObject = OwnerObject;
	AllColliders = {};

	// get the position and adjust for the size of the collider to center it
	float x = Position.x - HalfDimensions.x;
	float y = Position.y - HalfDimensions.y;
	// set the width and height of the rect to full size
	float w = HalfDimensions.x * 2;
	float h = HalfDimensions.y * 2;

	// set the bounds based on the above algorithms
	ColliderRect = { x, y, w, h };
}

Collider::~Collider()
{
	for (vector<Collider*>::iterator it = AllColliders.begin(); it < AllColliders.end(); ++it) {
		// check if the current iterated item is not this collider
		if ((*it) != this) {
			// since we return a boolean we can check if anything was removed
			// this can be run without the if statement - it's mainly just for debugging
			if ((*it)->RemoveColliderFromOverlapped(this)) {
				SDL_Log("Collider Removed from overlapped...");
			}
		}
	}
}

void Collider::Update(float DeltaTime, vector<Collider*> OtherColliders)
{
	AllColliders = OtherColliders;

	// Check if this collider is intersecting with any other colliders in the game
	for (unsigned int i = 0; i < OtherColliders.size(); ++i) {
		// make sure the otehrcollider isn't our collider
		if (OtherColliders[i] != this) {
			// detect if this collider is intersecting with any other colliders
			// SDL_HasIntersection will be true if the colliders intersect or false if they don't
			if (SDL_HasIntersectionF(&ColliderRect, &OtherColliders[i]->ColliderRect)) {
				// looking through the overlapped colliders array to detect if this collider is in there
				// this will pass an iterator number less than the end() if it's in the array
				vector<Collider*>::iterator it = find(OverlappedColliders.begin(), OverlappedColliders.end(), OtherColliders[i]);
				if (it == OverlappedColliders.end()) {
					OverlappedColliders.push_back(OtherColliders[i]);
					SDL_Log("Entered Collider");
				}
			}
			else {
				// check if the othercollider is in the overlapped array
				vector<Collider*>::iterator it = find(OverlappedColliders.begin(), OverlappedColliders.end(), OtherColliders[i]);
				// if it is then remove it from the array
				if (it < OverlappedColliders.end()) {
					OverlappedColliders.erase(it);
					SDL_Log("Exited Collider");
				}
			}
		}
	}
}

void Collider::Draw(SDL_Renderer* Renderer)
{
	if (bDebug == true) {
		//is the overlapped colliders empty?
		if (OverlappedColliders.empty()) {
			// set the sdl draw collour to red
			SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 1);
		}
		else {
			// set the sdl draw colour to green
			SDL_SetRenderDrawColor(Renderer, 0, 255, 0, 1);
		}
		// draw the red colour as a rectangle based on our collider dimensions
		SDL_RenderDrawRectF(Renderer, &ColliderRect);
	}
}

vector<Collider*> Collider::GetOverlappingColliders() const
{
	return OverlappedColliders;
}

GameObject* Collider::GetOwner() const
{
	return OwnerObject;
}

bool Collider::RemoveColliderFromOverlapped(Collider* RCollider)
{
	// iterate through the overlapped colliders to see if our RCollider is in there
	vector<Collider*>::iterator it = find(OverlappedColliders.begin(), OverlappedColliders.end(), RCollider);
	// if the collider is within the array
	if (it < OverlappedColliders.end()) {
		OverlappedColliders.erase(it);
		// if it was successfully erased return true
		return true;
	}

	//this will run if the if statement is false
	// nothing was erased
	return false;
}