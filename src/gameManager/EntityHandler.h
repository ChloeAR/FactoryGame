#pragma once

#include <vector>

#include "ResourceHandler.h"
#include "../entities/entityList.h"

class EntityHandler {
private:
	std::vector<TileEntity*> tileEntities;
	std::vector<ItemEntity*> itemEntities;

public:
	//Updates all tileEntities and itemEntities
	void update(sf::Time timeElapsed);
	//Draws all entities to screen
	void draw(sf::RenderWindow* window);
	//Clears the memory of all entity lists
	void freeEntities();
	
	//Creates a TileEntity at the given position.
	template<class TileType>
	TileEntity& newTile(ResourceHandler& resources, sf::Vector2f pos) {
		TileType* tile = new TileType(resources, pos);
		tileEntities.push_back(tile);

		return *tile;
	}

	//Creates a TileEntity at the Transformables position with the same rotation.
	template<class TileType>
	TileEntity& newTile(ResourceHandler& resources, sf::Transformable trans) {
		TileType* tile = new TileType(resources, trans.getPosition());
		tile->sprite.setOrigin(trans.getOrigin());
		tile->sprite.setRotation(trans.getRotation());
		tileEntities.push_back(tile);

		return *tile;
	}

	//Creates an ItemEntity at the given position.
	template<class ItemType>
	ItemEntity& newItem(ResourceHandler& resources, sf::Vector2f pos) {
		ItemType* item = new ItemType(resources, pos);
		itemEntities.push_back(item);

		return *item;
	}
};