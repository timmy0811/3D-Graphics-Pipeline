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
	Triangle(Point* p1, Point* p2, Point* p3, sf::Color color);

	void applyPerspective(float distance) override;
	void render(sf::RenderTarget* target) override;

	void moveByValue(sf::Vector3f dir) override;
	void moveToPos(sf::Vector3f pos) override;

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	void rotateX(float angle, sf::Vector3f refPosition) override;
	void rotateY(float angle, sf::Vector3f refPosition) override;
	void rotateZ(float angle, sf::Vector3f refPosition) override;

	void setGlobalOffset(sf::Vector3f* vec) override;

	double averageZ();
	double calculateProjectedZ();

	void createPoly(sf::RenderTarget* target);
};

