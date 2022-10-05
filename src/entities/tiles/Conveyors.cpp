#include "Conveyors.h"

Conveyor::Conveyor(const ResourceHandler& resources, sf::Vector2f pos, uint type)
	: TileEntity(resources.getTexture(1))
	, animator(8, 3, 16, 16) {
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite.setScale(4, 4);

	//Set Speed and graphics depending on what kind of conveyor it is
	switch (type) {
	case 1:
		animator.setFrames(0, 8);
		speedMillis = 150;
		break;
	case 2:
		animator.setFrames(9, 16);
		speedMillis = 75;
		break;
	case 3:
		animator.setFrames(17, 24);
		speedMillis = 50;
		break;
	}
	animator.setSpeed(speedMillis);

	placeSound.setBuffer(resources.getSound(0));
	placeSound.play();
};