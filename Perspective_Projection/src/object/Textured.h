#pragma once

#include "renderable/Renderable.h"
#include "Texture.h"

namespace projection {
	class Textured : public Renderable
	{
	protected:
		sf::Vector2u m_DimensionsReference;

		Texture* m_Texture;
		const sf::Uint8* m_TextureArray;

		const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y) const;

	public:
		Texture* getTexture();
	};
}


