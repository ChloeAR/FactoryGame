#pragma once

#include "../Entity.h"

class Machine : public TileEntity {
public:
	Machine(sf::Texture& text, sf::Vector2f pos)
		: TileEntity(text, pos) {}

	InventoryComponent& inventory() {
		return *inventory_;
	}

	// If machine has an inventory, we add an item to it.
	virtual void addItem(ItemEntity* item) {
		if (inventory_ != nullptr) { inventory_->items.push_back(item); }
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

	void addItem(ItemEntity* item) override {
		delete item;
	}

	ItemEntity* process(sf::Time timeElapsed) override {
		return NULL;
	}
};