#include "Renderable.h"

std::vector<AbstractObject*> Renderable::getChildren()
{
	return std::vector<AbstractObject*>();
}

std::vector<sf::VertexArray>* Renderable::getVertices()
{
	return &vertices;
}

void Renderable::setGlobalOffset(sf::Vector3f* vec)
{
	globalOffset_ = vec;
}

sf::Vector2f Renderable::translateToRel(sf::Vector2f pos, sf::Vector2u windowSize)
{
	return sf::Vector2f(pos.x * windowSize.y + windowSize.x / 2, pos.y * windowSize.y + windowSize.y / 2);
}

Renderable::Renderable()
{
}
