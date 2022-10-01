#pragma once

#include <SFML/Graphics.hpp>

#include "EntityHandler.h"
#include "ResourceHandler.h"

typedef unsigned int uint;

class gameManager {
private:
	/* Graphics - - - - - - - - - - - - - - - - - - - - - - - - - - */
	sf::RenderWindow gameWindow;


	/* Entities - - - - - - - - - - - - - - - - - - - - - - - - - - */
	//Maintains all tileEntities, itemEntities, etc
	EntityHandler EntityHandler_;
	//Maintains all sounds and textures
	ResourceHandler ResourceHandler_;

	
	/* Game Loop - - - - - - - - - - - - - - - - - - - - - - - - - */
	sf::Clock Clock_;

	//Handles events and updates gamestate
	void update();
	//Updates display
	void display();

public:
	//Game constructor taking window size arguments
	gameManager(uint gameWidth, uint gameHeight);

	//Processes game loop until window is closed.
	void run();
};