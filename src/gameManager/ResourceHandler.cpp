#include "ResourceHandler.h"

//Hardcoded for now
void ResourceHandler::initTextures() {
	auto tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/cursor_place.png");
	TextureMap.push_back(std::move(tmpPtr));

	tmpPtr = std::make_unique<sf::Texture>();
	tmpPtr->loadFromFile("data/textures/conveyor_one_spritesheet.png");
	TextureMap.push_back(std::move(tmpPtr));
}

void ResourceHandler::initSounds() {
	
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