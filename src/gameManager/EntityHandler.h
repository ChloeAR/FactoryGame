#pragma once

#include <vector>

#include "ResourceHandler.h"
#include "../entities/entityList.h"

#include <typeinfo>
#include <memory>

class Grabber;

class EntityHandler {
private:
	std::vector<TileEntity*> tileEntities;
	std::vector<ItemEntity*> itemEntities;
	
	std::vector<std::shared_ptr<Conveyor>> conveyorEntities;
	std::vector<Machine*> machineEntities;

public:
	//Updates all tileEntities and itemEntities
	void update(sf::Time timeElapsed);
	//Draws all entities to screen
	void draw(sf::RenderWindow* window);
	//Clears the memory of all entity lists
	void freeEntities();

	//Returns a shared pointer to a conveyor (if there is one) intersecting the specified pos. Otherwise returns nullptr.		
	std::shared_ptr<Conveyor> conveyorAtPoint(sf::FloatRect pos) const{
		for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
			if (conveyorEntities.at(i).get()->sprite.getGlobalBounds().intersects(pos)) {
				return conveyorEntities.at(i);
			}
		}

		return nullptr;
	}

	//Returns a reference to the TileEntity at a specified position
	TileEntity* tileAtPoint(sf::FloatRect pos) {
		for (unsigned int i = 0; i < tileEntities.size(); i++) {
			if (tileEntities.at(i)->sprite.getGlobalBounds().intersects(pos)) {
				return tileEntities.at(i);
			}
		}

		return nullptr;
	}
	
	//Creates a TileEntity of the specified type with specified arguments.
	template<class TileType, typename ...ARGS>
	TileType& newTile(ARGS && ...args) {
		TileType* tile = new TileType(std::forward<ARGS>(args)...);
		//Push conveyors and machines into separate vectors
		if (typeid(TileType) == typeid(Conveyor)) {
			std::shared_ptr<Conveyor> newTile((Conveyor*)tile);
			conveyorEntities.push_back(newTile);
			return *(TileType*)newTile.get();
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
		else if (typeid(TileType) == typeid(Grabber)) {
			machineEntities.push_back((Grabber*)tile);
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