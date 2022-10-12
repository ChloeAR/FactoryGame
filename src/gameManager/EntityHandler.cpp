#include "EntityHandler.h"

void EntityHandler::update(sf::Time timeElapsed) {
	//Call the updater for all TileEntities in the list
	for (unsigned int i = 0; i < tileEntities.size(); i++){
		tileEntities.at(i)->update(timeElapsed);
	}

	//Call the updater for all ConveyorEntities
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		conveyorEntities.at(i)->update(timeElapsed);
	}

	//Call the updater for all ItemEntities in the list 
	for (unsigned int i = 0; i < itemEntities.size(); i++) {
		itemEntities.at(i)->update(timeElapsed);

		//Check if unclaimed itemEntities are on a conveyor
		for (unsigned int j = 0; j < conveyorEntities.size(); j++) {
			if (itemEntities.at(i)->sprite.getGlobalBounds().intersects(conveyorEntities.at(j)->sprite.getGlobalBounds())) {
				conveyorEntities.at(j)->addItem(itemEntities.at(i));
				itemEntities.erase(itemEntities.begin() + i);
				break;
			}
		}
	}

	// Slide all items present in conveyors and return fallen items to the itemList
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		ItemEntity* temp = conveyorEntities.at(i)->slide(timeElapsed);
		if (temp != NULL) { itemEntities.push_back(temp); }
	}
}

void EntityHandler::draw(sf::RenderWindow* window) {
	//Draw all tileEntities in the list to the provided window
	for (unsigned int i = 0; i < tileEntities.size(); i++) {
		window->draw(tileEntities.at(i)->sprite);
	}

	//Draw all conveyors
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		window->draw(conveyorEntities.at(i)->sprite);
	}
	//Draw all conveyors' items
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		conveyorEntities.at(i)->displayItems(window);
	}
	
	//Draw all itemEntities in the list to the provided window
	for (unsigned int i = 0; i < itemEntities.size(); i++) {
		window->draw(itemEntities.at(i)->sprite);
	}
}

void EntityHandler::freeEntities() {
	//Clear tileEntities
	while (tileEntities.size() > 0) {
		delete tileEntities.back();
		tileEntities.pop_back();
	}

	//Clear itemEntities
	while (itemEntities.size() > 0) {
		delete itemEntities.back();
		itemEntities.pop_back();
	}

	//Clear conveyorEntities
	while (conveyorEntities.size() > 0) {
		delete conveyorEntities.back();
		conveyorEntities.pop_back();
	}
}
