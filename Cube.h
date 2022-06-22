#pragma once

#include <vector>

#include "Renderable.h"
#include "Point.h"

#include "MatrixOperations.h"

class Cube : public Renderable
{
private:
	std::vector<Point*> points;

	void createVert(int p1, int p2, sf::RenderTarget* target);

public:
	Cube(sf::Vector2f position, float size);

	void render(sf::RenderTarget* target);
	void applyPerspective(float distance);

	void rotateX(float angle);
	void rotateY(float angle);
	void rotateZ(float angle);

	void connect(sf::RenderTarget* target);

	std::vector<Point*>* getPoints();
};

