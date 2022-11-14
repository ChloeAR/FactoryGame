#pragma once
#include "../Entity.h"
#include "../Components.h"

#include <vector>

class Conveyor : public TileEntity {
private:
	AnimationComponent animator;

	uint speedMillis = 150;

	InventoryComponent inventory;

public:
	//Takes a reference to the game's ResourceHandler, as well as the position to create the object at.
	Conveyor(const ResourceHandler& resources, sf::Vector2f pos, uint type);

	virtual void update(sf::Time timeElapsed) {
		/* Visual Updates - - - - - - - - - - - - - - - - - - - - - - - - */
		animator.runSheet(this->sprite);
	}

	//Adds an item to the Conveyor's inventory
	void addItem(ItemEntity* item) {
		 { inventory.items.push_back(item); }
	}

	//Returns the last item on the conveyor
	ItemEntity* takeItem() {
		if (inventory.items.size() > 0) {
			ItemEntity* item = inventory.items.back();
			inventory.items.pop_back();
			return item;
		}
		return nullptr;
	}

	//Renders all of the items in the conveyor
	void displayItems(sf::RenderWindow* game);

	// Slides everything on the conveyor belt, returns an ItemEntity* if it falls off the conveyor.
	ItemEntity* slide(sf::Time timeElapsed);
};
