#pragma once

#include "Mesh.h"

namespace projection {
	class Plane : public Mesh
	{
	public:
		Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, sf::Color color);
		Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, Texture* texture);

		~Plane();

		void connect(sf::RenderTarget* target) override;
	};
}


