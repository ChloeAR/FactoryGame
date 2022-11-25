#pragma once

#include <stack>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "../EntityHandler.h"

typedef void (*Function_Ptr)();

struct Table_Entry {
	int expected;
	std::string title;
	Function_Ptr selectionFunc;
};

class Submenu {
public:
	Submenu(Table_Entry OptionArray[], size_t tableSize)
		: OptionTable(OptionArray)
		, TableSize(tableSize) {}


	Table_Entry* OptionTable;
	size_t TableSize;
};

static class Menu {
public:
	Menu() { 
		//Prepare menu
		Menus.push(&rootMenu);


		//Prepare display of menu
		textFont.loadFromFile("data/arial.ttf");
		menuText.setFont(textFont);
		menuText.setFillColor(sf::Color::Green);
		menuText.setCharacterSize(24);
		menuText.setPosition(20, 20);

		std::stringstream tempMenuText;
		for (int i = 0; i < Menus.top()->TableSize; i++) {
			tempMenuText << (Menus.top()->OptionTable)[i].expected << ")\t" << (Menus.top()->OptionTable)[i].title << "\n";
		}
	
		menuText.setString(tempMenuText.str());
	}

	void display(sf::RenderWindow& display) {
		display.draw(menuText);
	}

	//Pops the Submenu if input = 0, passing any other number to the active menu.
	void control(unsigned int i) {
		if (i == 0) {
			if (Menus.size() > 1) {
				Menus.pop();
			}
		}
		else { /* Process Options for menus*/ 
			if (Menus.top()->TableSize >= i) {
				(*Menus.top()->OptionTable[i - 1].selectionFunc)();
			}
		}

		//Reset Menu Text
		std::stringstream tempString;
		if (Menus.size() > 1) { tempString << "ESC)\t^ Return\n"; }
		for (int i = 0; i < Menus.top()->TableSize; i++) {
			tempString << i + 1 << ")\t" << Menus.top()->OptionTable[i].title << "\n";
		}

		menuText.setString(tempString.str());
	}

private:
	static std::stack<const Submenu*> Menus;

	static const Submenu rootMenu, buildMenu;

	static const Table_Entry rootMenu_[], buildMenu_[];
	static const size_t rootMenuSize, buildMenuSize;

	sf::Font textFont;
	sf::Text menuText;
	

private: // Submenu Function Declarations
	friend void openBuildMenu(), runDemo();
};

