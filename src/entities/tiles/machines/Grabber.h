#pragma once

#include <memory>

#include "../../../gameManager/EntityHandler.h"

#include "../Machine.h"
#include "../Conveyors.h"

class EntityHandler;

class Grabber : public Machine {
public:
	Grabber(const ResourceHandler& resources, sf::Vector2f pos, const EntityHandler& Entities);

	ItemEntity* process(sf::Time timeElapsed) override;

private:
	std::weak_ptr<Conveyor> conveyor;
	sf::Time grabWait = sf::seconds(0);

	const EntityHandler& EntityHandler_;
	sf::Vector2f destination = sf::Vector2f(-1,-1);
};