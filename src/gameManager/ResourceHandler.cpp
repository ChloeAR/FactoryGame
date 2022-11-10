#include "ResourceHandler.h"

//Hardcoded for now -> eventually store in a file
void ResourceHandler::initTextures() {
	auto tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/cursor_place.png");				//0
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/conveyor_one_spritesheet.png");	//1
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/items/ores.png");				//2
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/machines/furnace.png");			//3
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/machines/drill.png");			//4
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/machines/void.png");			//5
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/machines/grabber.png");			//6
	TextureMap.push_back(std::move(tmpPtr));
}

void ResourceHandler::initSounds() {
	auto tmpPtr = std::make_unique<sf::SoundBuffer>();
	tmpPtr->loadFromFile("data/audio/click1.wav");						//x 0
	SoundMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::SoundBuffer>();
	tmpPtr->loadFromFile("data/audio/smelt.wav");						//x 1
	SoundMap.push_back(std::move(tmpPtr));
}

ResourceHandler::ResourceHandler() {
	initTextures();
	initSounds();
}

sf::Texture& ResourceHandler::getTexture(unsigned short int id) const{
	return *TextureMap.at(id).get();
}

sf::SoundBuffer& ResourceHandler::getSound(unsigned short int id) const {
	return *SoundMap.at(id).get();
}