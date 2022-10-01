#include "Components.h"

AnimationComponent::AnimationComponent(uint columns, uint rows, uint pixelWidth, uint pixelHeight, uint milliseconds) {
	this->columns = columns; this->rows = rows; this->pixelWidth = pixelWidth;
	this->pixelHeight = pixelHeight; this->milliseconds = milliseconds;
}

void AnimationComponent::runSheet(sf::Sprite& sprite) {
	//Check that enough time has elapsed since previous update
	if (clock.getElapsedTime().asMilliseconds() > milliseconds) {
		clock.restart();

		//Shift the sprites textureRect to the next one
		sf::IntRect rect = sprite.getTextureRect();
		if (rect.left < ((columns - 1) * pixelWidth)) {
			rect.left = rect.left + pixelWidth;
		}
		else {
			rect.left = 0;
			if (rect.top < ((rows - 1) * pixelHeight)) {
				rect.top = rect.top + pixelHeight;
			}
			else { rect.top = 0; }
		}
		sprite.setTextureRect(rect);
	}
}