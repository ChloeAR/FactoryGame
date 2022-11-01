#pragma once

#include "../gameManager/ResourceHandler.h"
#include "Components.h"


class Entity {
public:
	sf::Sprite sprite;

	virtual void update(sf::Time timeElapsed) {}

protected:
	Entity(sf::Texture& texture) : sprite(texture) {}
};

class TileEntity : public Entity {
protected:
	TileEntity(sf::Texture& texture) : Entity(texture) {};

	sf::Sound placeSound;
};

class ItemEntity : public Entity {
protected:
	ItemEntity(sf::Texture& texture) : Entity(texture) {};

};