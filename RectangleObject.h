#pragma once
#include "GameObject.h"
class RectangleObject :
    public GameObject
{
public:
    RectangleObject(float width, float height, Vector2 Position, SDL_Colour Colour, bool bFilled = false);

    void Draw(SDL_Renderer* Renderer) override;

protected:
    float width;
    float height;
    // Screen position
    Vector2 Position;
    // this will decide if the rectangle is filled with colour or not
    bool bFilled;
    SDL_Colour Colour;
};

