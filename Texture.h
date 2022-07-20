#pragma once

#include <SFML/Graphics.hpp>

#include "Ressources.h"

class Texture
{
private:
	sf::Image* image;
	sf::Vector2u dim;

	Ressources* res;

public:
	Texture(Ressources* res);
	~Texture();

	void setTexture(TexType type);
	
	const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y);
	const sf::Uint8* getPixelPtr();

	sf::Vector2u getSize();
};