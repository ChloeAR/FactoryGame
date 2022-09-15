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
	void update();
	//Draws all entities to screen
	void draw(sf::RenderWindow* window);
	//Clears the memory of all entity lists
	void freeEntities();
	
	//Create a new tile entity and place it on the list
	template<class TileType>
	TileEntity& newTile(ResourceHandler& resources, sf::Vector2f pos) {
		TileType* tile = new TileType(resources, pos);
		tileEntities.push_back(tile);

		return *tile;
	}

	//Create a new item entity and place it on the list
	template<class ItemType>
	ItemEntity& newItem(ResourceHandler& resources, sf::Vector2f pos) {
		ItemType* item = new ItemType(resources, pos);
		itemEntities.push_back(item);

		return *item;
	}
};