#pragma once

#include "renderable/Renderable.h"
#include "Texture.h"

namespace projection {
	class Textured : public Renderable
	{
	protected:
		sf::Vector2u dimRef;

		Texture* texture;
		const sf::Uint8* textureArr;

		const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y);

	public:
		Texture* getTexture();
	};
}


