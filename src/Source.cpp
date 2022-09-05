#include "GameManager/gameManager.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	if (argc == 3) {
		gameManager Game(std::stoi(argv[1]), std::stoi(argv[2]));
		Game.run();
	}
	else {
		gameManager Game(1800, 940);
		Game.run();
	}
	
	return 0;
}