#pragma once

#include "Renderable.h"
#include "Texture.h"

class Textured : public Renderable
{
protected:
	sf::Vector2u dimRef;

	Texture* texture;
	const sf::Uint8* textureArr;

	const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y);
};

