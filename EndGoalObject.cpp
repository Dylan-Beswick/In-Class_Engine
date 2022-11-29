#include "EndGoalObject.h"
#include "Game.h"
#include "MSGameOver.h"

EndGoalObject::EndGoalObject(Vector2 Position, Vector2 Dimensions)
{
	this->Position = Position;
	this->ObjectCenter = Position;

	SetCollision(this->Position, Dimensions);

}

void EndGoalObject::Update(float DeltaTime)
{
	// Get overlapped colliders from the first collision
	vector<Collider*> OverCols = Collisions[0]->GetOverlappingColliders();

	// loop through the overlapped colliders and check if the player is within them
	// if so change the state to the menu state
	for (vector<Collider*>::iterator Col = OverCols.begin(); Col < OverCols.end(); Col++) {
		if ((*Col)->GetOwner()->Tag == "Player") {
			MSGameOver* NewState = new MSGameOver;
			Game::GetGameInstance()->ChangeGameState(NewState, 2);
		}
	}
}
