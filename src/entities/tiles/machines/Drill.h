#pragma once

#include "../Machine.h"

class EntityHandler;

class Drill : public Machine {
public:
	Drill(ResourceHandler* resources, sf::Vector2f pos, Metal::Type type = Metal::Type::Stone) : Machine(resources->getTexture(4), pos), ResourceHand_(resources), oreType(type) {
		sprite.setTextureRect(sf::IntRect(0, 0, 16, 16));
		sprite.setScale(4, 4);
	}

	//Spawn new ore every 3 seconds
	ItemEntity* process(sf::Time timeElapsed) override {
		timeDrilling = timeDrilling + timeElapsed;

		if (timeDrilling.asSeconds() > 3) {
			timeDrilling = sf::seconds(0);

			//Spawn a new metal on output of drill
			Metal* item = new Metal(*ResourceHand_, /*POSITION*/this->sprite.getPosition() + sf::Vector2f(32, -32), oreType);
			// Move item to output
			switch ((int)this->sprite.getRotation()) {
			case 90: {
				item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(32, -16));
				break;
			}
			case 180: {
				item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-12, 32));
				break;
			}
			case 270: {
				item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-32 - 24, -16));
				break;
			}
			case 0: {
				item->sprite.setPosition(this->sprite.getPosition() + sf::Vector2f(-12, -32 - 32));
				break;
			}
			}

			return item;
		}

		return nullptr;
	}

private:
	sf::Time timeDrilling = sf::seconds(0);

	Metal::Type oreType;

	//Pointer to game's resource bank for new Metals
	const ResourceHandler* ResourceHand_;
};