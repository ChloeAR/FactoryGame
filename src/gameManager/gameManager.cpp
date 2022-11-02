#include "gameManager.h"

void gameManager::demo() {
	for (int i = 0; i < 5; i++) {
		//Spawn Drills and Voids
		EntityHandler_.newTile<Drill>(&ResourceHandler_, sf::Vector2f(64, 128 * i + (64 * 4)), (Metal::Type)(i) );
		EntityHandler_.newTile<Trash>(ResourceHandler_, sf::Vector2f(64 * 9 + 128, 128 * i + (64 * 4)));

		//Conveyors and Furnaces
		for (int j = 0; j < 9; j++) {
			if (j == 4) {
				EntityHandler_.newTile<Furnace>(ResourceHandler_, sf::Vector2f(64 * j + 128, 128 * i + (64 * 4)), 3);
			}
			else {
				Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(64 * j + 128, 128 * i + (64 * 4)), 3);
				conv.sprite.rotate(90);
			}
		}
	}
}

void gameManager::update() {
	//Check for events
	sf::Event event;
	while (gameWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			//Free dynamically allocated memory before closing
			EntityHandler_.freeEntities();
			gameWindow.close();
		}
	}

	//Update component systems at most 60 times a second
	sf::Time timeElapsed = Clock_.getElapsedTime();
	if (timeElapsed.asMilliseconds() > 16) { 
		EntityHandler_.update(timeElapsed); Clock_.restart(); }
}

void gameManager::display() {
	sf::Time timeElapsed = DisplayClock_.getElapsedTime();
	if (timeElapsed.asMilliseconds() < 16) { return; }
	//Backsplash
	gameWindow.clear(sf::Color(75, 75, 76));

	//Update display
	EntityHandler_.draw(&gameWindow);

	//Push display
	gameWindow.display();

	DisplayClock_.restart();
}

gameManager::gameManager(uint gameWidth, uint gameHeight)
    : gameWindow(sf::VideoMode(gameWidth, gameHeight), "FactoryGame", sf::Style::Close) {
	
	//Center Screen (40 is approx taskbar height) 
	int xPos = (sf::VideoMode::getDesktopMode().width - gameWidth) / 2;
	int yPos = (sf::VideoMode::getDesktopMode().height - gameHeight) / 2 - 40;
	gameWindow.setPosition(sf::Vector2i(xPos, yPos));
}

void gameManager::run() {
	demo();

	while (gameWindow.isOpen()) {
		update();

		display();
	}
	return;
}
