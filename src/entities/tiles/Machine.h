#pragma once

#include "../Components.h"

class Machine : public TileEntity {
public:
	Machine(sf::Texture& text, sf::Vector2f pos)
		: TileEntity(text, pos) {}

	InventoryComponent& inventory() {
		return *inventory_;
	}

	// If machine has an inventory, we add an item to it. Returns false if no inventory component exists.
	virtual bool addItem(ItemEntity* item) {
		if (inventory_ != nullptr) { inventory_->items.push_back(item); return true; }
		else { return false; }
	}

	// Machine processes and returns an item to the global space.
	virtual ItemEntity* process(sf::Time timeElapsed) {
		return nullptr;
	}

	virtual ~Machine() {
		if (inventory_ != nullptr) {
			delete inventory_;
		}
	}

protected:
	InventoryComponent* inventory_ = nullptr;

};

class Trash : public Machine {
public:
	Trash(ResourceHandler& resources, sf::Vector2f pos) : Machine(resources.getTexture(5), pos) {}

	bool addItem(ItemEntity* item) override {
		delete item;
		return true;
	}

	ItemEntity* process(sf::Time timeElapsed) override {
		return NULL;
	}
};
