#include "gameManager.h"


void gameManager::update() {
	//Check for events
	sf::Event event;
	while (gameWindow.pollEvent(event)) {
		//Free dynamically allocated memory before closing
		if (event.type == sf::Event::Closed) {
			EntityHandler_.freeEntities();
			gameWindow.close();
		}
	}

	//Update component sytems
	EntityHandler_.update();
}

void gameManager::display() {
	//Backsplash
	gameWindow.clear(sf::Color(75, 75, 76));

	//Update display
	EntityHandler_.draw(&gameWindow);

	//Push display
	gameWindow.display();
}

gameManager::gameManager(uint gameWidth, uint gameHeight) : gameWindow(sf::VideoMode(gameWidth, gameHeight), "FactoryGame", sf::Style::Close) {
	//Center Screen (40 is approx taskbar height) 
	int xPos = (sf::VideoMode::getDesktopMode().width - gameWidth) / 2;
	int yPos = (sf::VideoMode::getDesktopMode().height - gameHeight) / 2 - 40;
	gameWindow.setPosition(sf::Vector2i(xPos, yPos));
}

void gameManager::run() {

	while (gameWindow.isOpen()) {
		update();

		display();
	}
	return;
}
