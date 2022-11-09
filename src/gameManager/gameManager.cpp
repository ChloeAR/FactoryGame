#include "gameManager.h"

void gameManager::inputHandler(sf::Event event) {
	const sf::Vector2f cursorPos = cursor.getPosition() - sf::Vector2f(32, 32);

	switch (event.key.code) {
		case sf::Keyboard::R: {
			cursor.rotate(90);
			break;
		}
		case sf::Keyboard::Num1: {
			Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, cursorPos, 3);
			conv.sprite.setRotation(cursor.getRotation());
			break;
		}
		case sf::Keyboard::Num2: {
			Drill& drill = EntityHandler_.newTile<Drill>(&ResourceHandler_, cursorPos, (Metal::Type::Iron));
			drill.sprite.setRotation(cursor.getRotation());
			break;
		}
		case sf::Keyboard::Num3: {
			Furnace& furnace = EntityHandler_.newTile<Furnace>(ResourceHandler_, cursorPos);
			furnace.sprite.setRotation(cursor.getRotation());
			break;
		}
		default: {}
	}
}

void gameManager::demo() {
	for (int i = 0; i < 5; i++) {
		//Spawn Drills and Voids
		EntityHandler_.newTile<Drill>(&ResourceHandler_, sf::Vector2f(64, 128 * i + (64 * 4)), (Metal::Type)(i) );
		EntityHandler_.newTile<Trash>(ResourceHandler_, sf::Vector2f(64 * 9 + 128, 128 * i + (64 * 4)));

		//Conveyors and Furnaces
		for (int j = 0; j < 9; j++) {
			if (j == 4) {
				EntityHandler_.newTile<Furnace>(ResourceHandler_, sf::Vector2f(64 * j + 128, 128 * i + (64 * 4)));
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

		// Handle Input
		if (event.type == sf::Event::KeyPressed) {
			inputHandler(event);
		}
	}

	//Update component systems at most 60 times a second
	sf::Time timeElapsed = Clock_.getElapsedTime();
	if (timeElapsed.asMilliseconds() > 16) { 
		//Update cursor
		sf::Vector2i mousePos = sf::Mouse::getPosition(gameWindow);
		mousePos.x = mousePos.x - (mousePos.x % 64) + 32;
		mousePos.y = mousePos.y - (mousePos.y % 64) + 32;
		cursor.setPosition(sf::Vector2f(mousePos));

		EntityHandler_.update(timeElapsed); Clock_.restart(); }
}

void gameManager::display() {
	sf::Time timeElapsed = DisplayClock_.getElapsedTime();
	if (timeElapsed.asMilliseconds() < 16) { return; }
	//Backsplash
	gameWindow.clear(sf::Color(75, 75, 76));

	//Update display
	EntityHandler_.draw(&gameWindow);
	gameWindow.draw(cursor);

	//Push display
	gameWindow.display();

	DisplayClock_.restart();
}

gameManager::gameManager(uint gameWidth, uint gameHeight)
    : gameWindow(sf::VideoMode(gameWidth, gameHeight), "FactoryGame", sf::Style::Close)
	, cursor(ResourceHandler_.getTexture(0)) {
	
	//Center Screen (40 is approx taskbar height) 
	int xPos = (sf::VideoMode::getDesktopMode().width - gameWidth) / 2;
	int yPos = (sf::VideoMode::getDesktopMode().height - gameHeight) / 2 - 40;
	gameWindow.setPosition(sf::Vector2i(xPos, yPos));

	//Set up UI
	cursor.setScale(4, 4);
	cursor.setOrigin(8, 8);
}

void gameManager::run() {
	//demo();

	while (gameWindow.isOpen()) {
		update();

		display();
	}
	return;
}
