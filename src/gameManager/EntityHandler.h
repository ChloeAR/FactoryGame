#pragma once

#include <vector>

#include "ResourceHandler.h"
#include "../entities/entityList.h"

#include <typeinfo>

class EntityHandler {
private:
	std::vector<TileEntity*> tileEntities;
	std::vector<ItemEntity*> itemEntities;
	
	std::vector<Conveyor*> conveyorEntities;
	std::vector<Machine*> machineEntities;

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
		//Push conveyors and machines into separate vectors
		if (typeid(TileType) == typeid(Conveyor)) {
			conveyorEntities.push_back((Conveyor*)tile);
		}
		else if (typeid(TileType) == typeid(Furnace)) {
			machineEntities.push_back((Furnace*)tile);
		}
		else if (typeid(TileType) == typeid(Drill)) {
			machineEntities.push_back((Drill*)tile);
		}
		else if (typeid(TileType) == typeid(Trash)) {
			machineEntities.push_back((Trash*)tile);
		}
		else { tileEntities.push_back(tile); }

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