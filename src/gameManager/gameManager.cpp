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
	//Restart clock
	sf::Time timeElapsed = Clock_.getElapsedTime();

	///////////////////////@@@@@@@@@@@@@@@@@@
	//Update component sytems with time since last update @ 60 FPS@
	if (timeElapsed.asMilliseconds() > 16) { 
		sf::Vector2i position = sf::Mouse().getPosition(gameWindow);
		position.x = position.x - (position.x % 64);
		position.y = position.y - (position.y % 64);
		MouseSprite.setPosition((sf::Vector2f)position);


		EntityHandler_.update(timeElapsed); Clock_.restart(); }
}

void gameManager::display() {
	//Backsplash
	gameWindow.clear(sf::Color(75, 75, 76));

	//Update display
	EntityHandler_.draw(&gameWindow);
	gameWindow.draw(MouseSprite);

	//Push display
	gameWindow.display();
}

gameManager::gameManager(uint gameWidth, uint gameHeight) : gameWindow(sf::VideoMode(gameWidth, gameHeight), "FactoryGame", sf::Style::Close),
															MouseSprite(ResourceHandler_.getTexture(0))
{
	//Center Screen (40 is approx taskbar height) 
	int xPos = (sf::VideoMode::getDesktopMode().width - gameWidth) / 2;
	int yPos = (sf::VideoMode::getDesktopMode().height - gameHeight) / 2 - 40;
	gameWindow.setPosition(sf::Vector2i(xPos, yPos));

	MouseSprite.setScale(4, 4);
}

void gameManager::run() {

	for (int i = 1; i < 10; i++) {
		EntityHandler_.newTile<Conveyor>(ResourceHandler_, sf::Vector2f(30, i * 64));
	}

	while (gameWindow.isOpen()) {
		update();

		display();
	}
	return;
}
