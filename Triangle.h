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

	void rotateX(float angle, sf::Vector3f refPosition) override;
	void rotateY(float angle, sf::Vector3f refPosition) override;
	void rotateZ(float angle, sf::Vector3f refPosition) override;

	double averageZ();
	double calculateProjectedZ();

	void translateToRelative(sf::RenderTarget* target);

	void createPoly(sf::RenderTarget* target);
};

