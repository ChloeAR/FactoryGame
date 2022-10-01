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

	//Takes the ID of a specified texture and returns a reference to the requested texture
	sf::Texture& getTexture(unsigned short int id) const;

	//Takes the ID of a specified soundbuffer and returns a reference to the requested soundbuffer.
	sf::SoundBuffer& getSound(unsigned short int id) const;
};