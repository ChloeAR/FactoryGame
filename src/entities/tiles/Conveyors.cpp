#include "Conveyors.h"

Conveyor::Conveyor(const ResourceHandler& resources, sf::Vector2f pos, uint type)
	: TileEntity(resources.getTexture(1))
	, animator(8, 3, 16, 16) {
	sprite.setPosition(pos);
	sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
	sprite.setScale(4, 4);

	//Set Speed and graphics depending on what kind of conveyor it is
	switch (type) {
	case 1:
		animator.setFrames(0, 8);
		speedMillis = 150;
		break;
	case 2:
		animator.setFrames(9, 16);
		speedMillis = 75;
		break;
	case 3:
		animator.setFrames(17, 24);
		speedMillis = 50;
		break;
	}
	animator.setSpeed(speedMillis);

	placeSound.setBuffer(resources.getSound(0));
	placeSound.play();
}

void Conveyor::addItem(ItemEntity* item) {
	inventory.items.push_back(std::pair<ItemEntity*, unsigned int>(item, 1));
}

void Conveyor::displayItems(sf::RenderWindow* game) {
	for (int i = 0; i < inventory.items.size(); i++) {
		game->draw(inventory.items.at(i).first->sprite);
	}
}

ItemEntity* Conveyor::slide(sf::Time timeElapsed) {
	/* Push Items - - - - - - -- -  -- - - - - -- - - - -- - - - - - - -*/
	float itemspeed = (float)timeElapsed.asMicroseconds() / this->speedMillis / 1000 * 4;
	for (int i = 0; i < inventory.items.size(); i++) {
		switch ((int)this->sprite.getRotation()) {
		case 0: {
			inventory.items.at(i).first->sprite.move(0, -itemspeed);
			break; }
		case 90: {
			inventory.items.at(i).first->sprite.move(itemspeed, 0);
			break; }
		case 180: {
			inventory.items.at(i).first->sprite.move(0, itemspeed);
			break; }
		case 270: {
			inventory.items.at(i).first->sprite.move(-itemspeed, 0);
			break; }
		}
	}

	//Test if fall off
	for (int i = 0; i < inventory.items.size(); i++) {
		if (!(inventory.items.at(i).first->sprite.getGlobalBounds().intersects(this->sprite.getGlobalBounds()))) {
			ItemEntity* temp = inventory.items.at(i).first;
			inventory.items.erase(inventory.items.begin() + i);
			return temp;
		}
	}

	return NULL;
}