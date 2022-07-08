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
	globalOffset_ = vec;
}

sf::Vector2f Renderable::translateToRel(sf::Vector2f pos, int windowSize)
{
	return sf::Vector2f(pos.x * windowSize + windowSize / 2, pos.y * windowSize + windowSize / 2);
}

