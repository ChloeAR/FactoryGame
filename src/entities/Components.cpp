#include "Components.h"

AnimationComponent::AnimationComponent(uint columns, uint rows, uint pixelWidth, uint pixelHeight) {
	this->columns = columns; this->rows = rows; this->pixelWidth = pixelWidth;
	this->pixelHeight = pixelHeight;

	firstFrame = 1;
	lastFrame = columns * rows;
	milliseconds = 500;
}

void AnimationComponent::runSheet(sf::Sprite& sprite) {
	
	//Check that enough time has elapsed since previous update
	if (clock.getElapsedTime().asMilliseconds() > milliseconds) {
		clock.restart();

		//Advance frame
		sf::IntRect rect = sprite.getTextureRect();
		if (currentFrame < lastFrame) {
			currentFrame++;
		}
		else {
			currentFrame = firstFrame;
		}

		//Shift the texture rectangle to be in the spot of the new frame
		unsigned int pixelsRight = (currentFrame - 1) * pixelWidth;
		unsigned int pixelsDown = 0;
		while (pixelsRight >= columns * pixelWidth) {
			pixelsRight = pixelsRight - (columns * pixelWidth);
			pixelsDown = pixelsDown + pixelHeight;
		}
		rect.left = pixelsRight;
		rect.top = pixelsDown;

		sprite.setTextureRect(rect);
	}
}

void AnimationComponent::setFrames(uint first, uint last) {
	//Handle if either is 0 (Pushes limit to the begininng or end)
	if (last == 0) { this->lastFrame = columns * rows; }
	else { this->lastFrame = last; }
	if (first == 0) { this->firstFrame = 1; }
	else { this->firstFrame = first; }

	currentFrame = firstFrame;

	//If the lastFrame is before the first one the animator will stay on the firstFrame.
	if (lastFrame < firstFrame) { lastFrame = firstFrame; }
}