#pragma once
#include "GameObject.h"
#include "Vector2.h"

class EndGoalObject :
    public GameObject
{
public:
    EndGoalObject(Vector2 Position, Vector2 Dimensions);

    virtual void Update(float DeltaTime) override;
};

