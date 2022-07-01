#pragma once

#include <vector>

#include "Renderable.h"
#include "Triangle.h"
#include "Point.h"

class Mesh : public Renderable
{
protected:
	std::vector<Triangle*> polys;

	void createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color);
	void sortPolys();

public:
	~Mesh();

	virtual void render(sf::RenderTarget* target);
};

