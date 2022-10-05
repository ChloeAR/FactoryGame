#pragma once
#include "../Entity.h"
#include <vector>

class Conveyor : public TileEntity {
private:
	AnimationComponent animator;

	uint speedMillis = 150;
//	std::vector<ItemEntity&> items;
public:
	//Takes a reference to the game's ResourceHandler, as well as the position to create the object at.
	Conveyor(const ResourceHandler& resources, sf::Vector2f pos, uint type);

	virtual void update(sf::Time timeElapsed) {
		/* Visual Updates - - - - - - - - - - - - - - - - - - - - - - - - */
		animator.runSheet(this->sprite);

		/* Interactions - - - - - - - - - - - - - - - - - - - - - - - - - - */
		//Adds an item onto the conveyor, or returns false if there is not room.
		//
	}
};
