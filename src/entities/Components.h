#pragma once
#include "SFML/Graphics.hpp"

typedef unsigned int uint;

class AnimationComponent {
private:
	//Amount of rows and columns of sprites.
	uint columns, rows;
	//Length and Width of each sprite.
	uint pixelWidth, pixelHeight;
	//Timekeeping for animation, how many milliseconds before the next frame
	sf::Clock clock; uint milliseconds;

public:
	//Creates an animator with specified columns, rows, where each rectangle has specified pixel dimensions.
	//A new frame will be drawn when it has been milliseconds since the last one.
	AnimationComponent(uint columns, uint rows, uint pixelWidth, uint pixelHeight, uint milliseconds);

	//Triggers the next frame as long as it has been at least [milliseconds]
	void runSheet(sf::Sprite& sprite);
};
