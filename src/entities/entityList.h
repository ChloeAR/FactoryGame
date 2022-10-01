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

};

class ItemEntity : public Entity {
protected:
	ItemEntity(sf::Texture& texture) : Entity(texture) {};

};

class Conveyor : public TileEntity {
private:
	AnimationComponent animator;
public:
	Conveyor(const ResourceHandler& resources, sf::Vector2f pos)
		: TileEntity(resources.getTexture(1))
		, animator(4,2,16,16,100) {
		sprite.setPosition(pos);
		sprite.setTextureRect(sf::IntRect(0,0,16,16));
		sprite.setScale(4, 4);
	};

	virtual void update(sf::Time timeElapsed) {
		/* Visual Updates - - - - - - - - - - - - - - - - - - - - - - - - */
		animator.runSheet(this->sprite);

		/* Interactions - - - - - - - - - - - - - - - - - - - - - - - - - - */
	}
};
