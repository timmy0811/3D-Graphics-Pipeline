#pragma once

#include <SFML/Graphics.hpp>

#include "Matrix3X1.h"
#include "MatrixOperations.h"

#include "Renderable.h"

class Point : public Renderable
{
private:
	Matrix3X1 position;
	Matrix3X1 projectedPositon;
	sf::CircleShape shape;

public:
	Point(sf::Vector3f position);

	void render(sf::RenderTarget* target);

	void setMatrix(Matrix3X1 mat);
	void setProjMatrix(Matrix3X1 mat);

	Matrix3X1* getMatrix();
	Matrix3X1* getProjMatrix();

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

};

