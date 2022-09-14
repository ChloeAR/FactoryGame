#include "EntityHandler.h"

void EntityHandler::update() {
	//Loop through tileEntities
	for (int i = 0; i < itemEntities.size(); i++){
		tileEntities.at(i)->update();
	}

	//Loop through itemEntities
	for (int i = 0; i < itemEntities.size(); i++) {
		itemEntities.at(i)->update();
	}
}

void EntityHandler::draw(sf::RenderWindow* window) {
	for (int i = 0; i < tileEntities.size(); i++) {
		window->draw(tileEntities.at(i)->sprite);
	}
	
	for (int i = 0; i < itemEntities.size(); i++) {
		window->draw(itemEntities.at(i)->sprite);
	}
}