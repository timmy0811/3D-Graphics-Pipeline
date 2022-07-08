#pragma once

#include <SFML/Graphics.hpp>

#include "Matrix3X1.h"
#include "Matrix3X3.h"

class Renderable
{
protected:
	Renderable();

	sf::RenderTarget* target;

	std::vector<sf::VertexArray> vertices;
	sf::Color color;

	sf::Vector3f* globalOffset_;

public:
	virtual void render(sf::RenderTarget* target) = 0;
	virtual void applyPerspective(float distance_) = 0;

	virtual void rotateX(float angle) = 0;
	virtual void rotateY(float angle) = 0;
	virtual void rotateZ(float angle) = 0;

	virtual void rotateX(float angle, sf::Vector3f refPosition) = 0;
	virtual void rotateY(float angle, sf::Vector3f refPosition) = 0;
	virtual void rotateZ(float angle, sf::Vector3f refPosition) = 0;

	virtual void moveByValue(sf::Vector3f dir) = 0;
	virtual void moveToPos(sf::Vector3f pos) = 0;

	std::vector<sf::VertexArray>* getVertices();
	virtual void setGlobalOffset(sf::Vector3f* vec);

	sf::Vector2f translateToRel(sf::Vector2f pos, int windowSize);
};

