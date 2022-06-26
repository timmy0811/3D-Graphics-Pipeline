#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

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

	void render(sf::RenderTarget* target) override;
	void applyPerspective(float distance) override;

	void setMatrix(Matrix3X1 mat);
	void setProjMatrix(Matrix3X1 mat);

	Matrix3X1* getMatrix();
	Matrix3X1* getProjMatrix();

	sf::Vector3f getPosition();
	sf::Vector3f getProjPosition();

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	std::vector<Point*>* getPoints();
};

