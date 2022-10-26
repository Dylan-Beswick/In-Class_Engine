#pragma once
#include "Character.h"
#include "Vector2.h"

class Player :
    public Character
{
public:
    Player(Texture* CharacterTexture, Vector2 Pos, int NumberOfFrames = 1);
    ~Player();

    void Update(float DeltaTime) override;
    void ProcessInput(Input* UserInput) override;
};

