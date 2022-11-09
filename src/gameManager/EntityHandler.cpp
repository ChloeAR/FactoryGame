#include "EntityHandler.h"

void EntityHandler::update(sf::Time timeElapsed) {
	//Call the updater for all TileEntities in the list
	for (unsigned int i = 0; i < tileEntities.size(); i++){
		tileEntities.at(i)->update(timeElapsed);
	}

	//Call the updater for all ConveyorEntities
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		conveyorEntities.at(i).get()->update(timeElapsed);
	}

	//Call the updater for all ItemEntities in the list 
	for (unsigned int i = 0; i < itemEntities.size(); i++) {
		itemEntities.at(i)->update(timeElapsed);

		//Check if unclaimed itemEntities are on a conveyor
		for (unsigned int j = 0; j < conveyorEntities.size(); j++) {
			if (itemEntities.at(i)->sprite.getGlobalBounds().intersects(conveyorEntities.at(j).get()->sprite.getGlobalBounds())) {
				conveyorEntities.at(j).get()->addItem(itemEntities.at(i));
				itemEntities.erase(itemEntities.begin() + i);
				break;
			}
		}

		//Prevent OOB
		if (i >= itemEntities.size()) { return; }

		//Check if unclaimed entities are in a machine
		for (unsigned int j = 0; j < machineEntities.size(); j++) {
			if (itemEntities.at(i)->sprite.getGlobalBounds().intersects(machineEntities.at(j)->sprite.getGlobalBounds())) {
				machineEntities.at(j)->addItem(itemEntities.at(i));
				itemEntities.erase(itemEntities.begin() + i);
				break;
			}

		}

		//Prevent OOB
		if (i >= itemEntities.size()) { return; }
	}

	// Slide all items present in conveyors and return fallen items to the itemList
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		ItemEntity* temp = conveyorEntities.at(i).get()->slide(timeElapsed);
		if (temp != NULL) { itemEntities.push_back(temp); }
	}

	// Process all machines and return items into the global itemList
	for (unsigned int i = 0; i < machineEntities.size(); i++) {
		ItemEntity* temp = machineEntities.at(i)->process(timeElapsed);
		if (temp != nullptr) { itemEntities.push_back(temp); }
	}
}

void EntityHandler::draw(sf::RenderWindow* window) {
	//Draw all tileEntities in the list to the provided window
	for (unsigned int i = 0; i < tileEntities.size(); i++) {
		window->draw(tileEntities.at(i)->sprite);
	}

	//Draw all conveyors
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		window->draw(conveyorEntities.at(i).get()->sprite);
	}
	//Draw all conveyors' items
	for (unsigned int i = 0; i < conveyorEntities.size(); i++) {
		conveyorEntities.at(i).get()->displayItems(window);
	}
	
	//Draw all other machines
	for (unsigned int i = 0; i < machineEntities.size(); i++) {
		window->draw(machineEntities.at(i)->sprite);
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
		conveyorEntities.back().reset();
		conveyorEntities.pop_back();
	}

	//Clear machineEntities
	while (machineEntities.size() > 0) {
		delete machineEntities.back();
		machineEntities.pop_back();
	}
}

