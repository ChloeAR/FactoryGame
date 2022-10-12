#include "gameManager.h"

void gameManager::demo() {
	for (int i = 0; i < 8; i++) {
		EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(64, 64 * i + 64), 3);
		Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(64 * i + 128 + 32, 64 * 8 - 32), 1);
		conv.sprite.setOrigin(8, 8);
		conv.sprite.setRotation(270);

		Conveyor& conv2 = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(64 * i + 128, 0), 3);
		conv2.sprite.setRotation(90);

		Conveyor& conv3 = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(512 + 128, i * 64), 3);
		conv3.sprite.setRotation(180);
	}
	
	Metal& met = EntityHandler_.newItem<Metal>(ResourceHandler_, sf::Vector2f(64 + 16, 64 * 9 + 16), Metal::Type::Copper);
	met.smelt();
	for (int i = 0; i < 4; i++) {
		EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128 * i + 128, 64 * 8 ), 2);
		EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128 * i + 128, 64 * 9), 2);
		EntityHandler_.newItem<Metal>(ResourceHandler_, sf::Vector2f(128 * i + 128 + 16, 64 * 9 + 16), Metal::Type::Iron);
		EntityHandler_.newItem<Metal>(ResourceHandler_, sf::Vector2f(128 * i + 128 + 16, 64 * 8 + 16), Metal::Type::Copper);

		Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128 * i + 128, 0), 3);
		conv.sprite.setRotation(90);
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
