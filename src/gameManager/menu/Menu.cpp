#include "Menu.h"
#include "../gameManager.h"

//Forward decs

// Menu Related Menus
void openBuildMenu(); void openConveyorsMenu(); void openMachinesMenu(); void runDemo(); void openOresMenu();

// Conveyor Related Menu Options
inline void spawnConveyor(int); 
inline void spawnConv1() { spawnConveyor(1); }
inline void spawnConv2() { spawnConveyor(2); }
inline void spawnConv3() { spawnConveyor(3); }

// Machine Related Menu Options
void spawnMachine(int);
inline void spawnDrill() { spawnMachine(1); }
inline void spawnFurnace() { spawnMachine(2); }
inline void spawnGrabber() { spawnMachine(3); }

// Ore Related Menu Options
void spawnOre(int);
void spawnCopper() { spawnOre(1); }
void spawnIron() { spawnOre(2); }
void spawnGold() { spawnOre(3); }

void spawnTrash() { Menu::EntHandler->newTile<Trash>(*Menu::ResHandler, Menu::cursor->getPosition() - sf::Vector2f(32, 32)); }

void reset() {
	Menu::EntHandler->freeEntities();
}  


const Submenu Menu::rootMenu((Table_Entry*)(rootMenu_), rootMenuSize);
const Submenu Menu::buildMenu((Table_Entry*)(buildMenu_), buildMenuSize);
const Submenu Menu::conveyorMenu((Table_Entry*)(conveyorMenu_), conveyorMenuSize);
const Submenu Menu::machinesMenu((Table_Entry*)(machinesMenu_), machinesMenuSize);
const Submenu Menu::oresMenu((Table_Entry*)(oresMenu_), oresMenuSize);

std::stack<const Submenu*> Menu::Menus;

const Table_Entry Menu::rootMenu_[] = {
	{1, "[ Build ]", &openBuildMenu},
	{2, "Reset", &reset},
	{3, "Demo", &runDemo}
}; const size_t Menu::rootMenuSize = sizeof(rootMenu_) / sizeof(rootMenu_[0]);

const Table_Entry Menu::buildMenu_[] = {
	{1, "[ Conveyors ]", &openConveyorsMenu},
	{2, "[ Machines ]", &openMachinesMenu},
	{3, "[ Ores ]", &openOresMenu},
	{4, "Trash", &spawnTrash}
}; const size_t Menu::buildMenuSize = sizeof(buildMenu_) / sizeof(buildMenu_[0]);

const Table_Entry Menu::conveyorMenu_[] = {
	{1, "Speed 1", (&spawnConv1)},
	{2, "Speed 2", (&spawnConv2)},
	{3, "Speed 3", (&spawnConv3)}
}; const size_t Menu::conveyorMenuSize = sizeof(conveyorMenu_) / sizeof(conveyorMenu_[0]);

const Table_Entry Menu::machinesMenu_[] = {
	{1, "Drill", (&spawnDrill)},
	{2, "Furnace", (&spawnFurnace)},
	{3, "Grabber", (&spawnGrabber)}
}; const size_t Menu::machinesMenuSize = sizeof(machinesMenu_) / sizeof(machinesMenu_[0]);

const Table_Entry Menu::oresMenu_[] = {
	{2, "Copper", (&spawnCopper)},
	{3, "Iron", (&spawnIron)},
	{4, "Gold", (&spawnGold)}
}; const size_t Menu::oresMenuSize = sizeof(oresMenu_) / sizeof(oresMenu_[0]);

void openBuildMenu() { Menu::Menus.push(&Menu::buildMenu); }
void openConveyorsMenu() { Menu::Menus.push(&Menu::conveyorMenu); }
void openMachinesMenu() { Menu::Menus.push(&Menu::machinesMenu); }
void openOresMenu() { Menu::Menus.push(&Menu::oresMenu); }

void runDemo() { Menu::game->demo(); }

void spawnConveyor(int i) {
	Conveyor& conv = Menu::EntHandler->newTile<Conveyor>(*Menu::ResHandler, Menu::cursor->getPosition() - sf::Vector2f(32, 32), i);
	conv.sprite.setRotation(Menu::cursor->getRotation());
}

void spawnMachine(int i) {
	Machine* machine = nullptr;
	sf::Vector2f pos = Menu::cursor->getPosition() - sf::Vector2f(32, 32);

	switch (i) {
	  case 1: {
		TileEntity* tile = Menu::EntHandler->tileAtPoint(sf::FloatRect(pos, sf::Vector2f(16, 16)));
		if (tile == nullptr) { return; }
		else if (typeid(*tile) == typeid(Ore)) {
			machine = &Menu::EntHandler->newTile<Drill>(Menu::ResHandler, pos, ((Ore*)tile)->type());
		}
		break;
	  }
	  case 2: {
		  machine = &Menu::EntHandler->newTile<Furnace>(*Menu::ResHandler, pos);
		  break;
	  }
	  case 3: {
		  machine = &Menu::EntHandler->newTile<Grabber>(*Menu::ResHandler, pos, *Menu::EntHandler);
		  break;
	  }
	  default: {
		  return;
	  }
	}

	if (machine != nullptr) { machine->sprite.setRotation(Menu::cursor->getRotation()); }
	return;
}

void spawnOre(int i) {
	Menu::EntHandler->newTile<Ore>(*Menu::ResHandler, Menu::cursor->getPosition() - sf::Vector2f(32, 32), (Metal::Type)(i));
}

Menu::Menu(gameManager* game) {
	//Prepare menu
	Menus.push(&rootMenu);
	Menu::game = game;
	Menu::EntHandler = &(game->EntityHandler_);
	Menu::ResHandler = &(game->ResourceHandler_);
	Menu::cursor = &(game->cursor);

	//Prepare display of menu
	textFont.loadFromFile("data/arial.ttf");
	menuText.setFont(textFont);
	tutoText.setFont(textFont);
	menuText.setFillColor(sf::Color::Green);
	tutoText.setFillColor(sf::Color::Green);
	menuText.setCharacterSize(24);
	tutoText.setCharacterSize(20);
	menuText.setPosition(20, 20);

	std::stringstream tempMenuText;
	for (int i = 0; i < Menus.top()->TableSize; i++) {
		tempMenuText << (Menus.top()->OptionTable)[i].expected << ")\t" << (Menus.top()->OptionTable)[i].title << "\n";
	}

	menuText.setString(tempMenuText.str());
	tutoText.setString("- Press R to rotate -\n- Drills can be placed on Ores to make Metal\n- Metal can be processes in a smelter");
	tutoText.setPosition((Menu::game->gameWindow.getSize().x / 2) - (tutoText.getGlobalBounds().width / 2), 30);
}