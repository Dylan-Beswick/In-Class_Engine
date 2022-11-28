#include "Text.h"

Text::Text()
{
	Colour = { 255, 255, 255, 255 };
	Font = nullptr;
	TextBox = { 0 };
	TextSurface = nullptr;
	TextTexture = nullptr;
	bShouldUpdateText = false;
}

Text::~Text()
{
	// deallocate the texture from memory
	if (TextTexture != nullptr) {
		SDL_DestroyTexture(TextTexture);
		TextTexture = nullptr;
	}

	// deallocate the font
	if (Font != nullptr) {
		TTF_CloseFont(Font);
		Font = nullptr;
	}
}

bool Text::InitialiseFont(SDL_Renderer* Renderer, string FontPath, int FontSize, string TextToRenderer, const SDL_Colour Colour, Vector2 Position)
{
	// initialise our global variables
	this->TextToRenderer = TextToRenderer;
	this->Colour = Colour;
	this->Position = Position;

	// Load the font
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);

	// Turn the font into a texture
	if (!SetText(Renderer)) {
		// if the font couldn't be set then fail
		return false;
	}

	// return true if able to create the text
	return SetText(Renderer);
}

void Text::Draw(SDL_Renderer* Renderer)
{

}

void Text::ChangeText(string NewText)
{
}

Vector2 Text::GetTextDimensions()
{
	return Vector2();
}

void Text::CenterText()
{
}

bool Text::SetText(SDL_Renderer* Renderer)
{
	// make sure the font loaded correctly
	if (Font == nullptr) {
		// if Font is nullptr then it couldn't find the path
		SDL_Log("Font not found...");

		return false;
	}

	// Create a surface of the font and message
	TextSurface = TTF_RenderText_Solid(Font, TextToRenderer.c_str(), Colour);

	// make sure the surface loaded correctly
	if (TextSurface == nullptr) {
		// if the Surface failed to create
		SDL_Log("Text Surface - Failed");

		return false;
	}

	// if there is already a texture assigned
	if (TextTexture != nullptr) {
		// destroy it and make room for a new text
		SDL_DestroyTexture(TextTexture);
		TextTexture = nullptr;
	}

	// Create the texture from the surface
	TextTexture = SDL_CreateTextureFromSurface(Renderer, TextSurface);

	// make sure the texture loaded correctly
	if (TextTexture == nullptr) {
		// if the texture failed to create
		SDL_Log("Text Texture - Failed");

		// deallocate the surface if the texture failed
		SDL_FreeSurface(TextSurface);

		return false;
	}

	TextBox = { Position.x, Position.y, TextSurface->w, TextSurface->h };

	// deallocate the surface
	SDL_FreeSurface(TextSurface);

	return true;

}
