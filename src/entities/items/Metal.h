#pragma once

#include "../Entity.h"

class Metal : public ItemEntity {
public:
	enum class Stage {Ore, Bar};
	enum class Type { Stone, Copper, Iron, Gold, Coal };

	Metal(const ResourceHandler& resources, sf::Vector2f pos, Metal::Type type);

	//Turns Metal into the next stage
	void smelt();

private:
	Stage stage = Stage::Ore;
	Type type;
};