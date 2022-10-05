#pragma once
#include "SFML/Graphics.hpp"

typedef unsigned int uint;

class AnimationComponent {
private:
	//Amount of rows and columns of sprites.
	uint columns, rows;
	//Length and Width of each sprite.
	uint pixelWidth, pixelHeight;
	
	uint firstFrame, lastFrame, currentFrame = 1;
	//Timekeeping for animation, how many milliseconds before the next frame
	sf::Clock clock; uint milliseconds;

public:
	//Creates an animator with specified columns, rows, where each rectangle has specified pixel dimensions.
	//A new frame will be drawn when it has been milliseconds since the last one.
	AnimationComponent(uint columns, uint rows, uint pixelWidth, uint pixelHeight);

	//Triggers the next frame as long as it has been at least [milliseconds]
	void runSheet(sf::Sprite& sprite);

	//Sets the animation component to push a new frame every [milliseconds]
	void setSpeed(uint milliseconds) { this->milliseconds = milliseconds; }

	//Limit the spritesheet to only use [first, last] frames in the animation.
	//A zero in either position will run from the beginning or until the end, respectively.
	void setFrames(uint first, uint last);
};
