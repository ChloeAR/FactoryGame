#pragma once

#include <vector>
#include <memory>

#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"


class ResourceHandler {
private:
	std::vector<std::unique_ptr<sf::Texture>> TextureMap;
	std::vector<std::unique_ptr<sf::SoundBuffer>> SoundMap;

	void initTextures();
	void initSounds();

public:
	//Initialize Resource Maps
	ResourceHandler();
	sf::Texture& getTexture(unsigned short int id) const;
	sf::SoundBuffer& getSound(unsigned short int id) const;
};