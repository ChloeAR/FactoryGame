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
	
	//Creates a TileEntity of the specified type with specified arguments.
	template<class TileType, typename ...ARGS>
	TileType& newTile(ARGS && ...args) {
		TileType* tile = new TileType(std::forward<ARGS>(args)...);
		tileEntities.push_back(tile);

		return *tile;
	}

	//Creates an ItemEntity of the specified type with specified arguments.
	template<class ItemType, typename ...ARGS>
	ItemType& newItem(ARGS && ...args) {
		ItemType* item = new ItemType(std::forward<ARGS>(args)...);
		itemEntities.push_back(item);

		return *item;
	}
};