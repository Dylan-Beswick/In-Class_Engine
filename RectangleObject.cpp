#include "RectangleObject.h"

RectangleObject::RectangleObject(float width, float height, Vector2 Position, SDL_Colour Colour, bool bFilled)
{
	this->width = width;
	this->height = height;
	this->Position = Position;
	this->Colour = Colour;
	this->bFilled = bFilled;
}


void RectangleObject::Draw(SDL_Renderer* Renderer)
{
	SDL_FRect Rectangle = { width, height, Position.x, Position.y };

	SDL_SetRenderDrawColor(Renderer, Colour.r, Colour.g, Colour.b, Colour.a);

	// if bFilled == false
	if (!bFilled) {
		// draw outline rectangle
		SDL_RenderDrawRectF(Renderer, &Rectangle);
	}
	else {
		// draw rectangle with filled colour
		SDL_RenderFillRectF(Renderer, &Rectangle);
	}
}
