#pragma once

#include <stack>

#include "SFML/Graphics.hpp"

class Menu;

class Submenu {
public:
	Submenu(std::string label = "") : label_(label) {}

	std::string label() { return this->label_; }

	void add(Submenu* menuPointer) {
		Submenus.emplace_back(menuPointer);
	}

	friend bool operator==(const Submenu menu, const std::string str) {
		return (menu.label_ == str);
	}

private:
	std::string label_;

	//Contains submenus
	std::vector<Submenu*> Submenus;
};


class Menu {
public:
	Menu();

	//Displays the menu
	void display(sf::RenderWindow& display) {
		
	}

	//Pops the Submenu if input = 0, passing any other number to the active menu.
	void control(unsigned int i) {
		if (i == 0) { 
			if (Menus.size() > 1) {
				Menus.pop();
			}
		}
		else { /* Process Options for menus*/ }
	}

private:
	std::stack<Submenu*> Menus;

	Submenu root, Build;

	Submenu Conveyors, Machines, Ores;

};


