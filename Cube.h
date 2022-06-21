#pragma once

#include <vector>

#include "Renderable.h"
#include "Point.h"

#include "MatrixOperations.h"

class Cube : public Renderable
{
private:
	std::vector<Point> points;
	std::vector<sf::Vertex[2]> vertices;

	void createVert(float p1, float p2);

public:
	Cube(sf::Vector2f position, float size);

	void render(sf::RenderTarget* target);

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void connect();
};

