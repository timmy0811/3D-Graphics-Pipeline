#pragma once

#include <SFML/Graphics.hpp>

#include "Matrix3X1.h"
#include "Matrix3X3.h"

class Renderable
{
protected:
	Renderable();

public:
	virtual void render(sf::RenderTarget* target) = 0;

	virtual void rotateX(float angle) = 0;
	virtual void rotateY(float angle) = 0;
	virtual void rotateZ(float angle) = 0;

	sf::Vector2f translateToRel(sf::Vector2f pos, int windowSize);
};

