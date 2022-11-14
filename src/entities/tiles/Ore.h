#pragma once

#include <random>

#include "../Entity.h"

#include "../items/Metal.h" 

class Ore : public TileEntity {
public:
	Ore(const ResourceHandler& resources, sf::Vector2f pos, Metal::Type type) 
	  : TileEntity(resources.getTexture(2), pos), type_(type) {

		sprite.setScale(4, 4);
		sprite.setTextureRect(sf::IntRect(rand() % 5 * 16, (int)type_ * 16, 16, 16));
	}

	const Metal::Type& type() {
		return type_;
	}

private:
	Metal::Type type_;

};