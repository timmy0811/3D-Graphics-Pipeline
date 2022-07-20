#include "Textured.h"

const sf::Uint8* Textured::getPixelPtr(unsigned int x, unsigned int y)
{
	if (x >= dimRef.x) x = dimRef.x - 1;
	if (y >= dimRef.y) y = dimRef.y - 1;

	return textureArr + (y * dimRef.x + x) * 4;
}
