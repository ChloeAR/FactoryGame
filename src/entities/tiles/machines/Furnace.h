#pragma once

#include "../Machine.h"

class Furnace : public Machine {
public:
	Furnace(const ResourceHandler& resources, sf::Vector2f pos, ...) : Machine(resources.getTexture(3), pos) {
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		inventory_ = new InventoryComponent;
		sprite.setScale(4, 4);

		smeltSound.setBuffer(resources.getSound(1));
		smeltSound.setLoop(true);
	}

	~Furnace() override{
		delete inventory_;
		inventory_ = nullptr;
		smeltSound.stop();
	}

	void update(sf::Time timeElapsed) override {}

	//Smelts the item on the bottom of the stack and outputs it
	ItemEntity* process(sf::Time timeElapsed) override{
		if (inventory_->items.size() > 0) {
			if (smelting == false) {
				smelting = true;
				sprite.setTextureRect(sf::IntRect(16, 0, 16, 16));

				smeltSound.play();
			}
		}
		else { 
			smelting = false;
			sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));

			smeltSound.pause();
		}

		if (smelting) {
			timeSmelting = timeSmelting + timeElapsed;

			if (timeSmelting.asSeconds() > 2) {
				Metal* item = (Metal*)inventory_->items.front();

				item->smelt();

				// Move item to output
				switch ((int)this->sprite.getRotation()) {
				case 90: {
					item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(32, -22));
					break;
				}
				case 180: {
					item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-18, 32));
					break;
				}
				case 270: {
					item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-32 - 44, -22));
					break;
				}
				case 0: {
					item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-22, -32 - 36));
					break;
				}
				}

				inventory_->items.erase(inventory_->items.begin());
				timeSmelting = sf::seconds(0);
				return item;
			}
		}

		return nullptr;
	}

private:
	bool smelting = false;
	sf::Time timeSmelting = sf::seconds(0);

	sf::Sound smeltSound;
};