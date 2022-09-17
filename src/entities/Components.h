#pragma once
#include "SFML/Graphics.hpp"

typedef unsigned int uint;

class AnimationComponent {
private:
	//Amount of rows and columns of sprites.
	uint columns, rows;
	//Length and Width of each sprite.
	uint pixelWidth, pixelHeight;

public:
	AnimationComponent(uint columns, uint rows, uint pixelWidth, uint pixelHeight) {
		this->columns = columns; this->rows = rows; this->pixelWidth = pixelWidth; this->pixelHeight = pixelHeight;
	}

	void runSheet(sf::Sprite& sprite) {
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
};
