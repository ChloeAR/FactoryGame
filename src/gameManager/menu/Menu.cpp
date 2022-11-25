#include "Menu.h"

//Forward decs
void runDemo();
void openBuildMenu(); void deleteHere() {} void openConveyorsMenu() {} void openMachinesMenu() {} void openOresMenu() {} void spawnTrash() {}

const Submenu Menu::rootMenu((Table_Entry*)(rootMenu_), rootMenuSize);
const Submenu Menu::buildMenu((Table_Entry*)(buildMenu_), buildMenuSize);

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


void openBuildMenu() { Menu::Menus.push(&Menu::buildMenu); }
void runDemo() {

}
