#include "EntityHandler.h"

void EntityHandler::update(sf::Time timeElapsed) {
	//Call the updater for all TileEntities in the list
	for (unsigned int i = 0; i < tileEntities.size(); i++){
		tileEntities.at(i)->update(timeElapsed);
	}

	//Call the updater for all ItemEntities in the list 
	for (unsigned int i = 0; i < itemEntities.size(); i++) {
		itemEntities.at(i)->update(timeElapsed);
	}
}

void EntityHandler::draw(sf::RenderWindow* window) {
	//Draw all tileEntities in the list to the provided window
	for (unsigned int i = 0; i < tileEntities.size(); i++) {
		window->draw(tileEntities.at(i)->sprite);
	}
	
	//Draw all itemEntities in the list to the provided window
	for (unsigned int i = 0; i < itemEntities.size(); i++) {
		window->draw(itemEntities.at(i)->sprite);
	}
}

void EntityHandler::freeEntities() {
	while (tileEntities.size() > 0) {
		delete tileEntities.back();
		tileEntities.pop_back();
	}

	while (itemEntities.size() > 0) {
		delete itemEntities.back();
		itemEntities.pop_back();
	}
}
