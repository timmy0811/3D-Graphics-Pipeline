#include "Mesh.h"

void Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle poly = Triangle(p1->getPosition(), p2->getPosition(), p3->getPosition(), color);
	polys.push_back(&poly);
}

Mesh::~Mesh()
{
	for (Triangle* poly : polys) {
		delete poly;
	}
}
