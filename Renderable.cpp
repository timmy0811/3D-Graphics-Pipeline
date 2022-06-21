#include "Renderable.h"

Renderable::Renderable()
{
	
}

sf::Vector2f Renderable::translateToRel(sf::Vector2f pos, int windowSize)
{
	return sf::Vector2f(pos.x * windowSize / 2 + windowSize / 2, pos.y * windowSize / 2 + windowSize / 2);
}

