#pragma once
#include "GameObject.h"

class Character :
	public GameObject
{
public:
	Character(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames);
	~Character();

	void Update(float DeltaTime);
};

