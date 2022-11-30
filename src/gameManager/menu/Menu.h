#pragma once

#include <stack>
#include <sstream>

#include "SFML/Graphics.hpp"

#include "../EntityHandler.h"
#include "../ResourceHandler.h"

class gameManager;

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

class Menu {
public:
	Menu(gameManager*);

	void display(sf::RenderWindow& display) {
		display.draw(menuText);
		display.draw(tutoText);
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
	// This is really bad and would be fine if I knew about function pointers when I started x(
	inline static gameManager* game;
	inline static EntityHandler* EntHandler;
	inline static ResourceHandler* ResHandler;
	inline static sf::Sprite* cursor;

	static std::stack<const Submenu*> Menus;

	static const Submenu rootMenu, buildMenu, conveyorMenu, machinesMenu, oresMenu;

	static const Table_Entry rootMenu_[], buildMenu_[], conveyorMenu_[], machinesMenu_[], oresMenu_[];
	static const size_t rootMenuSize, buildMenuSize, conveyorMenuSize, machinesMenuSize, oresMenuSize;

	sf::Font textFont;
	sf::Text menuText;
	sf::Text tutoText;

private: // Submenu Function Declarations
	friend void openBuildMenu(), runDemo(), openConveyorsMenu(), openMachinesMenu(), openOresMenu(), spawnConveyor(int), spawnMachine(int), spawnOre(int);
	friend void spawnTrash(), reset();
};

