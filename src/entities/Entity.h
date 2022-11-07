#pragma once

#include "../gameManager/ResourceHandler.h"
#include "Components.h"


class Entity {
public:
	sf::Sprite sprite;

	virtual void update(sf::Time timeElapsed) {}

	virtual ~Entity() {}

protected:
	Entity(sf::Texture& texture) : sprite(texture) {}
};

class TileEntity : public Entity {
public:
	virtual ~TileEntity() {}

protected:
	TileEntity(sf::Texture& texture, sf::Vector2f& pos) : Entity(texture) {
		sprite.setPosition(pos + sf::Vector2f(32, 32));
		sprite.setOrigin(8, 8);
		sprite.setScale(4, 4);
	}

	sf::Sound placeSound;
};

class ItemEntity : public Entity {
public:
	virtual ~ItemEntity() {}
protected:
	ItemEntity(sf::Texture& texture) : Entity(texture) {};
};