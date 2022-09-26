#pragma once

#include <SFML/Graphics.hpp>

namespace projection {
	// Texture enumerator
	enum class TexType { BRICKS = 0 , DIAMOND, DROPPER, ANDESIT};

	class Ressources {
	private:
		std::map<TexType, sf::Image*> textures;

	public:
		Ressources();

		sf::Image* getTexture(TexType type);
		sf::Vector2u getDim(TexType type);
	};
}
