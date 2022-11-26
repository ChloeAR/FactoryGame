#include "Menu.h"
#include "../gameManager.h"

//Forward decs

void openBuildMenu(); void openConveyorsMenu(); void openMachinesMenu() {}
void runDemo(); void deleteHere() {} void openOresMenu() {} void spawnTrash() {} void spawnConveyor() {}

const Submenu Menu::rootMenu((Table_Entry*)(rootMenu_), rootMenuSize);
const Submenu Menu::buildMenu((Table_Entry*)(buildMenu_), buildMenuSize);
const Submenu Menu::conveyorMenu((Table_Entry*)(conveyorMenu_), conveyorMenuSize);
//const Submenu Menu::machinesMenu((Table_Entry*)(machinesMenu_), machinesMenuSize);

std::stack<const Submenu*> Menu::Menus;

const Table_Entry Menu::rootMenu_[] = {
	{1, "[ Build ]", &openBuildMenu},
	{2, "Delete", &deleteHere},
	{3, "Demo", &runDemo}
}; const size_t Menu::rootMenuSize = sizeof(rootMenu_) / sizeof(rootMenu_[0]);

const Table_Entry Menu::buildMenu_[] = {
	{1, "[ Conveyors ]", &openConveyorsMenu},
	{2, "[ Machines ]", &openMachinesMenu},
	{3, "[ Ores ]", &openOresMenu},
	{4, "Trash", &spawnTrash}
}; const size_t Menu::buildMenuSize = sizeof(buildMenu_) / sizeof(buildMenu_[0]);

const Table_Entry Menu::conveyorMenu_[] = {
	{1, "Speed 1", (&spawnConveyor)},
	{2, "Speed 2", (&spawnConveyor)},
	{3, "Speed 3", (&spawnConveyor)}
}; const size_t Menu::conveyorMenuSize = sizeof(conveyorMenu_) / sizeof(conveyorMenu_[0]);

/*const Table_Entry Menu::machinesMenu_[] = {
	//Machines here
}; const size_t Menu::machinesMenuSize = sizeof(machinesMenu_) / sizeof(machinesMenu_[0]);*/

void openBuildMenu() { Menu::Menus.push(&Menu::buildMenu); }
void openConveyorsMenu() { Menu::Menus.push(&Menu::conveyorMenu); }
//void openMachinesMenu() { Menu::Menus.push(&Menu::machinesMenu); }

void runDemo() { Menu::game->demo(); }


Menu::Menu(gameManager* game) {
	//Prepare menu
	Menus.push(&rootMenu);
	Menu::game = game;

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