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
	void addItem(ItemEntity* item) {
		if (inventory_ != nullptr) { inventory_->items.push_back(item); }
	}

	// Machine processes and returns an item to the global space.
	virtual ItemEntity* process(sf::Time timeElapsed) {
		return nullptr;
	}

	virtual ~Machine() {}

protected:
	InventoryComponent* inventory_ = nullptr;

};

class Trash : public Machine {
public:
	Trash(ResourceHandler& resources, sf::Vector2f pos) : Machine(resources.getTexture(5), pos) {
		
		inventory_ = new InventoryComponent; }

	ItemEntity* process(sf::Time timeElapsed) override {
		if (inventory_->items.size() > 0) {
			delete inventory_->items.front();
			inventory_->items.erase(inventory_->items.begin());
		}
		return NULL;
	}
};