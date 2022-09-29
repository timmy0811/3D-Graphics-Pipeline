#include "Textured.h"

const sf::Uint8* projection::Textured::getPixelPtr(unsigned int x, unsigned int y) const
{
	if (x >= m_DimensionsReference.x) x = m_DimensionsReference.x - 1;
	if (y >= m_DimensionsReference.y) y = m_DimensionsReference.y - 1;

	return m_TextureArray + (y * m_DimensionsReference.x + x) * 4;
}

projection::Texture* projection::Textured::getTexture()
{
	return m_Texture;
}
