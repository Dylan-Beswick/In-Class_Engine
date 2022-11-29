#pragma once
#include "SDL.h"
#include <iostream>
#include <string>
#include "Vector2.h"
// using the SDL font library
#include "SDL_ttf.h"

using namespace std;

class Text
{
public:
	Text();
	~Text();

	// initialisr the fonts and return a boolean
	// @param FontPath - The path to the font in you project
	// @param TextToRender - The text that will be rendered to the screen
	bool InitialiseFont(SDL_Renderer* Renderer, string FontPath, int FontSize, string TextToRenderer, const SDL_Colour Colour, Vector2 Position = Vector2(0.0f, 0.0f));

	// Draw the font to the renderer
	void Draw(SDL_Renderer* Renderer);

	// Update text with new text
	void ChangeText(string NewText);

	// Get the width and height of the textbox
	Vector2 GetTextDimensions();

	// Center the text using its dimensions
	void CenterText(bool bCenterText);

protected:
	// this will actually define and render the text
	bool SetText(SDL_Renderer* Renderer);

	// this will store a font - this is not the text just the font file
	TTF_Font* Font;
	// to render to the screen we need a surface and a texture
	// surface converts to the screen
	SDL_Surface* TextSurface;
	// texture renders to the screen
	SDL_Texture* TextTexture;
	// Rectangle to render from the texture
	SDL_Rect TextBox;
	// bool to decide if we need to update the text
	bool bShouldUpdateText;
	// center text bool
	bool bCenterText;
	// Text rendering variables
	// Colour
	SDL_Colour Colour;
	// Text to render to the renderer
	string TextToRenderer;
	// Position of the text on the screen
	Vector2 Position;

};

