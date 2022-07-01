#include "Mesh.h"

void Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle* poly = new Triangle(p1->getPosition(), p2->getPosition(), p3->getPosition(), color);
	polys.push_back(poly);
}

Mesh::~Mesh()
{
	for (Triangle* poly : polys) {
		delete poly;
	}
}

void Mesh::render(sf::RenderTarget* target)
{
	for (Triangle* poly : polys) {
		poly->render(target);
	}
}

void Mesh::sortPolys()
{
	unsigned int swaps = 1;
	while (swaps > 0) {
		swaps = 0;
		for (int i = 0; i < polys.size(); i++) {
			if (i + 1.f >= polys.size()) continue;
			if (polys[static_cast<std::vector<Triangle*, std::allocator<Triangle*>>::size_type>(i) + 1]->averageZ() < polys[i]->averageZ()) {
				Triangle* tempPoly = polys[i];
				polys[i] = polys[i + 1.f];
				polys[i + 1.f] = tempPoly;
				swaps++;
			}
		}
	}
}
