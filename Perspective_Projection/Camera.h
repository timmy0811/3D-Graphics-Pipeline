#pragma once

#include <SFML/Graphics.hpp>
#include "Matrix.h"
#include "Matrix3X3.h"
#include "Matrix3X1.h"
#include "MatrixOperations.h"

class Camera
{
private:
	sf::Vector3f globalOffset_;

	sf::Vector3f position;
	sf::Vector2f rotation_;

public:
	Camera(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), sf::Vector2f rotation_ = sf::Vector2f(0.f, 0.f));

	void move(sf::Vector3f direction);
	void rotate(sf::Vector2f angle);

	sf::Vector3f* getOffset();
};

