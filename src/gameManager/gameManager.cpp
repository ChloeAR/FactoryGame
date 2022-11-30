#include "gameManager.h"

void gameManager::inputHandler(sf::Event event) {
	const sf::Vector2f cursorPos = cursor.getPosition() - sf::Vector2f(32, 32);

	if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9) {
		menu.control((int)event.key.code - 26);
	}

	switch (event.key.code) {
		case sf::Keyboard::R: {
			cursor.rotate(90);
			break;
		}
		case sf::Keyboard::Escape: {  
			menu.control(0);
			break;
		}
		default: {}
	}
}

void gameManager::demo() {
	for (int i = 0; i < 5; i++) {
		int ypos = (256) + (64 * i);
		if(i==0){ EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128, ypos - 64), 2); }
		if (i == 2) { EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128, ypos), 2); Conveyor& conv2 = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(256 + 128, ypos), 1); conv2.sprite.rotate(180); continue; }
		EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128, ypos), 3);

		Grabber& grabby = EntityHandler_.newTile<Grabber>(ResourceHandler_, sf::Vector2f(128 + 64, ypos), EntityHandler_);
		grabby.sprite.rotate(90);
		Furnace& furny = EntityHandler_.newTile<Furnace>(ResourceHandler_, sf::Vector2f(256, ypos));
		Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(256 + 64, ypos), 2);
		conv.sprite.rotate(90);
		furny.sprite.rotate(90);

		Conveyor& conv2 = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(256 + 128, ypos), 1);
		conv2.sprite.rotate(180);
	}

	EntityHandler_.newTile<Trash>(ResourceHandler_, sf::Vector2f(128+256, 576));
	for (int i = 0; i < 3; i++) {
		Conveyor& conv = EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(128 - 64 + (64 * i), 576), 2);
		conv.sprite.setRotation(-90 * (i - 1));
		EntityHandler_.newTile<Ore>(ResourceHandler_, sf::Vector2f(128 - 64 + (64 * i), 576 + 64), (Metal::Type)(i + 1));
		EntityHandler_.newTile<Drill>(&ResourceHandler_, sf::Vector2f(128 - 64 + (64 * i), 576 + 64), (Metal::Type)(i + 1));
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
	menu.display(gameWindow);
	gameWindow.draw(cursor);

	//Push display
	gameWindow.display();

	DisplayClock_.restart();
}

gameManager::gameManager(uint gameWidth, uint gameHeight)
    : gameWindow(sf::VideoMode(gameWidth, gameHeight), "FactoryGame", sf::Style::Close)
	, cursor(ResourceHandler_.getTexture(0)) 
	, menu(this) {
	
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
