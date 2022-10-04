#include <iostream>
#include "Texture.h"
#include "SDL_image.h"
using namespace std;

Texture::Texture()
{
	// set default texture to nullptr
	SdlTexture = nullptr;

	// set the width and height to 0
	width = 0;
	height = 0;
}

Texture::~Texture()
{
	ResetTexture();
}

bool Texture::LoadImageFromFile(const char* path, SDL_Renderer* renderer)
{
	if (SdlTexture == nullptr) {
		// Load the image to the surface
		SDL_Surface* LoadSurface = IMG_Load(path);

		if (LoadSurface != nullptr) {
			cout << "Load Texture - success" << endl;

			//create the texture from the surface
			SdlTexture = SDL_CreateTextureFromSurface(renderer, LoadSurface);

			if (SdlTexture != nullptr) {
				cout << "Create texture from surface - success" << endl;

				//get the dimensions of the image
				width = LoadSurface->w;
				height = LoadSurface->h;
			}
			else {
				cout << "Create texture from surface - failed" << endl;
			}

			SDL_FreeSurface(LoadSurface);
		}
		else {
			cout << "Load Texture - failed: " << SDL_GetError() << endl;
		}
	}
	else {
		cout << "Remove the existing texture before loading..." << endl;
		return false;
	}

	// if the sdltexture != nullptr then return true otherwise return false
	return SdlTexture != nullptr;
}

void Texture::Draw(SDL_Renderer* renderer, int x, int y, SDL_Rect* SourceRect, 
	int Scale, bool Flip)
{
	// set hte rendering space and render dimensions of the texture
	SDL_Rect DestinationRect = { x, y, width, height };

	// clip/crop the image if we have a source rect
	if (SourceRect != nullptr) {
		DestinationRect.w = SourceRect->w * Scale;
		DestinationRect.h = SourceRect->h * Scale;
	}

	SDL_RendererFlip FlipFlag = SDL_FLIP_NONE;

	if (Flip) {
		FlipFlag = SDL_FLIP_HORIZONTAL;
	}

	// render to the screen
	SDL_RenderCopyEx(renderer, SdlTexture, SourceRect, &DestinationRect, 0, 0, FlipFlag);
}

void Texture::ResetTexture()
{
	// deallocate texture
	if (SdlTexture != nullptr) {
		SDL_DestroyTexture(SdlTexture);
		SdlTexture = nullptr;
		width = 0;
		height = 0;
	}
}
