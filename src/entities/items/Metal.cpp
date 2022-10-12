#include "Metal.h"

Metal::Metal(const ResourceHandler& resources, sf::Vector2f pos, Metal::Type type)
	: ItemEntity(resources.getTexture(2)) {
	sprite.setPosition(pos);
	sprite.setScale(4, 4);
	sprite.setTextureRect(sf::IntRect(85, 8 + 16 * (int)type, 6, 8));
	this->type = type;
}

void Metal::smelt() {
	stage = Stage::Bar;
	sprite.setTextureRect(sf::IntRect(96, 16 * (int)type, 16, 16));
}