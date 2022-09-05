#pragma once

#include <SFML/Graphics.hpp>
typedef unsigned int uint;

class gameManager {
private:
	/* Graphics  - - - - - - - - - - - - - - - - - - - - - - - - - */
	sf::RenderWindow gameWindow;
	
	/* Game Loop - - - - - - - - - - - - - - - - - - - - - - - - - */
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