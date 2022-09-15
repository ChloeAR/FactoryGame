#pragma once
#include "../gameManager/ResourceHandler.h"

class Entity {
public:
	sf::Sprite sprite;

	virtual void update() {

	}
protected:
	Entity(sf::Texture& texture) : sprite(texture) {}
};

class TileEntity : public Entity {
protected:
	TileEntity(sf::Texture& texture) : Entity(texture) {};

};

class ItemEntity : public Entity {
protected:
	ItemEntity(sf::Texture& texture) : Entity(texture) {};

};

class Conveyor : public TileEntity {
public:
	Conveyor(const ResourceHandler& resources, sf::Vector2f pos) : TileEntity(resources.getTexture(1)) {
		sprite.setPosition(pos);
		sprite.setTextureRect(sf::IntRect(0,0,16,16));
		sprite.setScale(4, 4);
	};
};