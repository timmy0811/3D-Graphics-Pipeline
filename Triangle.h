#pragma once

#include "Renderable.h"
#include "Point.h"

class Triangle : public Renderable
{
private:
	Point* p1;
	Point* p2;
	Point* p3;

public:
	Triangle(sf::Vector3f pos1, sf::Vector3f pos2, sf::Vector3f pos3, sf::Color color);

	void applyPerspective(float distance) override;
	void render(sf::RenderTarget* target) override;

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	void createPoly(sf::RenderTarget* target);
};

