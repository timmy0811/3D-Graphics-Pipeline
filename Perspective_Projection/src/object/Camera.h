#pragma once

#include <SFML/Graphics.hpp>

#include "../misc/matrix/Matrix.h"
#include "../misc/matrix/Matrix3X3.h"
#include "../misc/matrix/Matrix3X1.h"
#include "../misc/matrix/MatrixOperations.h"

#include "renderable/Renderable.h"

namespace projection {
	class Camera
	{
	private:
		sf::Vector3f m_GlobalOffset;

		sf::Vector3f m_Position;
		sf::Vector2f m_Rotation;

	public:
		Camera(sf::Vector3f position = sf::Vector3f(0.f, 0.f, -1.f), sf::Vector2f rotation_ = sf::Vector2f(0.f, 0.f));

		void move(sf::Vector3f direction);
		void rotate(sf::Vector2f angle, std::vector<Renderable*> sceneObjects);

		sf::Vector3f* getOffset();
	};
}


