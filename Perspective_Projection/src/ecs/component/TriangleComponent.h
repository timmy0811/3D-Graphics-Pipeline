
#include <SFML/Graphics.hpp>

struct TriangleComponent {
	uint32_t p1;
	uint32_t p2;
	uint32_t p3;

	sf::Vector2f texCord1_{};
	sf::Vector2f texCord2_{};
	sf::Vector2f texCord3_{};
};