
#include <SFML/Graphics.hpp>
#include "../../object/Texture.h"

struct TextureComponent {
	sf::Vector2u dimRef;
	Texture* texture;
	const sf::Uint8* texArr;
};