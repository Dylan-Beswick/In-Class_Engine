#include "Animation.h"
#include <iostream>

using namespace std;

Animation::Animation()
{
}

Animation::Animation(Texture* InSpriteSheet, int InNumberOfFrames, 
	float InFrameDuration, int InStartFrame, int InEndFrame)
{
	// set default variables
	SpriteSheet = InSpriteSheet;
	StartFrame = InStartFrame;
	EndFrame = InEndFrame;
	FrameDuration = InFrameDuration;
	FrameTimer = 0.0f;
	CurrentFrame = StartFrame;

	// set the width and height of each sprite in the spritesheet
	if (SpriteSheet != nullptr) {
		// splice the spritesheet into its frames
		FrameWidth = SpriteSheet->GetImageWidth() / SDL_max(1, InNumberOfFrames);
		FrameHeight = SpriteSheet->GetImageHeight();
	}
	else {
		cout << "No texture provided in animation" << endl;
	}
}
Animation::~Animation()
{
	// if there is a spritesheet
	if (SpriteSheet != nullptr) {
		// deallocate the spritesheet
		delete SpriteSheet;
		SpriteSheet = nullptr;
	}
}

void Animation::Update(float DeltaTime)
{
	// Update the timer each frame
	FrameTimer += DeltaTime;

	// if the frame timer has passed the frame duration
	if (FrameTimer >= FrameDuration) {
		CurrentFrame++;

		FrameTimer = 0.0f;

		if (CurrentFrame >= EndFrame) {
			CurrentFrame = StartFrame;
		}
	}
}

void Animation::Draw(SDL_Renderer* Renderer, int PosX, int PosY, int Scale, bool Flip)
{
	// get the current rendering frame clipping region
	SDL_Rect clip;
	clip.x = CurrentFrame * FrameWidth;
	clip.y = 0;
	clip.w = FrameWidth;
	clip.h = FrameHeight;

	// draw to the screen
	SpriteSheet->Draw(Renderer, PosX, PosY, &clip, Scale, Flip);
}
