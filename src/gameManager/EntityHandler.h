#pragma once
#include <vector>
#include "ResourceHandler.h"


class Entity {
public:
	sf::Sprite sprite;

	virtual void update() {
	
	}

	Entity(sf::Texture& texture) : sprite(texture) {}
};

class TileEntity : public Entity {

};

class ItemEntity : public Entity {

};


class EntityHandler {
private:
	std::vector<TileEntity*> tileEntities;
	std::vector<ItemEntity*> itemEntities;

public:
	//Updates all tileEntities and itemEntities
	void update();
	//Draws all entities to screen
	void draw(sf::RenderWindow* window);
};