#include "Renderable.h"

std::vector<projection::AbstractObject*> projection::Renderable::getChildren()
{
	return std::vector<AbstractObject*>();
}

std::vector<sf::VertexArray>* projection::Renderable::getVertices()
{
	return &m_Vertices;
}

void projection::Renderable::setGlobalOffset(sf::Vector3f* vec)
{
	m_GlobalOffset = vec;
}

sf::Vector2f projection::Renderable::translateToRel(sf::Vector2f pos, sf::Vector2u windowSize)
{
	return sf::Vector2f(pos.x * windowSize.y + windowSize.x / 2, pos.y * windowSize.y + windowSize.y / 2);
}

projection::Renderable::Renderable()
{
}
