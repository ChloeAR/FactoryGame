#include "Grabber.h"

Grabber::Grabber(const ResourceHandler& resources, sf::Vector2f pos, const EntityHandler& Entities)
	: Machine(resources.getTexture(6), pos)
	, EntityHandler_(Entities) {
	sprite.setScale(4, 4);

}

ItemEntity* Grabber::process(sf::Time timeElapsed) {
	grabWait = grabWait + timeElapsed;
	if (grabWait.asSeconds() > 3) {
		if (!conveyor.expired()) {
			ItemEntity* item = conveyor.lock().get()->takeItem();
			//Move item to end of grabber
			if (item != nullptr) {
				item->sprite.setPosition(destination);

				grabWait = sf::seconds(0);
				return item;
			}
		}
		else {
			//no conveyor in entrypoint
			sf::FloatRect rectangle;

			//set entyrpoint conveyor
			switch ((int)sprite.getRotation()) {
			case 0: {
				sf::FloatRect rectangle(sprite.getPosition().x - 32, sprite.getPosition().y + 32, 64, 64);
				conveyor = EntityHandler_.conveyorAtPoint(rectangle);
				break;
			}
			case 90: {
				sf::FloatRect rectangle(sprite.getPosition().x - 32 - 64, sprite.getPosition().y - 32, 64, 64);
				conveyor = EntityHandler_.conveyorAtPoint(rectangle);
				break;
			}
			case 180: {
				sf::FloatRect rectangle(sprite.getPosition().x - 32, sprite.getPosition().y - 32 - 64, 64, 64);
				conveyor = EntityHandler_.conveyorAtPoint(rectangle);
				break;
			}
			case 270: {
				sf::FloatRect rectangle(sprite.getPosition().x + 32, sprite.getPosition().y - 32, 64, 64);
				conveyor = EntityHandler_.conveyorAtPoint(rectangle);
				break;
			}
			}
			
			

			//Set destination
			if (destination.x == -1) {
				switch ((int)sprite.getRotation()) {
				case 0: {
					destination = sprite.getPosition() + sf::Vector2f(0 - 16, -64);
					break;
				}
				case 90: {
					destination = sprite.getPosition() + sf::Vector2f(32, -16);
					break;
				}
				case 180: {
					destination = sprite.getPosition() + sf::Vector2f(0 - 16, 32);
					break;
				}
				case 270: {
					destination = sprite.getPosition() + sf::Vector2f(-32 - 32, -16);
					break;
				}
				}
			}
			grabWait = sf::seconds(0);
		}

	}

	return nullptr;
}