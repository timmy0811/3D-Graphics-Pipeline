#pragma once

#include <vector>

#include "Renderable.h"
#include "Triangle.h"
#include "Point.h"

class Mesh : public Renderable
{
protected:
	std::vector<Triangle*> polys;
	std::vector<Point*> points;

	bool wireFrame;

	void createVert(int p1, int p2, sf::RenderTarget* target);
	void createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color);
	void sortPolys();

public:
	~Mesh();

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	void applyPerspective(float distance) override;
	void virtual connect(sf::RenderTarget* target) = 0;

	virtual void render(sf::RenderTarget* target);

	std::vector<Point*>* getPoints();
};

