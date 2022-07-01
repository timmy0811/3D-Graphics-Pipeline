#include "Renderable.h"

Renderable::Renderable()
{
	
}

std::vector<sf::VertexArray>* Renderable::getVertices()
{
	return &vertices;
}

void Renderable::setGlobalOffset(sf::Vector3f* vec)
{
	globalOffset = vec;
}

sf::Vector2f Renderable::translateToRel(sf::Vector2f pos, int windowSize)
{
	return sf::Vector2f((pos.x + (*globalOffset).x) * windowSize / 2 + windowSize / 2, (pos.y + (*globalOffset).y) * windowSize / 2 + windowSize / 2);
}

