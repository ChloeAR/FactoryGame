#pragma once
#include "../Entity.h"
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

	// Adds an itemEntity* to this conveyors Inventory
	void addItem(ItemEntity* item);

	//Renders all of the items in the conveyor
	void displayItems(sf::RenderWindow* game);

	// Slides everything on the conveyor belt, returns an ItemEntity* if it falls off the conveyor.
	ItemEntity* slide(sf::Time timeElapsed);
};
