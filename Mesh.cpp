#include "Mesh.h"

void Mesh::createVert(int p1, int p2, sf::RenderTarget* target)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = translateToRel(sf::Vector2f(points[p1]->getProjMatrix()->x0, points[p1]->getProjMatrix()->y0), target->getSize().x);
	line[1].position = translateToRel(sf::Vector2f(points[p2]->getProjMatrix()->x0, points[p2]->getProjMatrix()->y0), target->getSize().x);

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	vertices.push_back(line);
}

void Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle* poly = new Triangle(p1, p2, p3, color);
	poly->setGlobalOffset(globalOffset_);
	polys.push_back(poly);
}

Mesh::~Mesh()
{
	for (Triangle* poly : polys) {
		delete poly;
	}

	for (Point* point : points) {
		delete point;
	}
}

void Mesh::rotateX(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateX(angle, pos);
	}
}

void Mesh::rotateY(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateY(angle, pos);
	}
}

void Mesh::rotateZ(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateZ(angle, pos);
	}
}

void Mesh::rotateX(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::rotateY(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::rotateZ(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::moveByValue(sf::Vector3f dir)
{
	for (Point* point : points) {
		point->moveByValue(dir);
	}
}

void Mesh::moveToPos(sf::Vector3f pos)
{
	for (Point* point : points) {
		point->moveToPos(pos);
	}
}

void Mesh::setGlobalOffset(sf::Vector3f* vec)
{
	for (Point* point : points) {
		point->setGlobalOffset(vec);
	}
	for (Triangle* poly : polys) {
		poly->setGlobalOffset(vec);
	}
}

void Mesh::applyPerspective(float distance_)
{
	for (Point* p : points) {
		p->applyPerspective(distance_);
	}

	connect(target);

	if (!wireFrame_) {
		for (Triangle* poly : polys) {
			poly->applyPerspective(distance_);
		}
	}
}

void Mesh::render(sf::RenderTarget* target)
{
	for (Point* p : points) {
		//p->render(target);
	}

	for (int i = 0; i < vertices.size(); i++) {
		target->draw(vertices[i]);
	}

	sortPolys();

	for (Triangle* poly : polys) {
		poly->render(target);
	}
}

std::vector<Point*>* Mesh::getPoints()
{
	return &points;
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
				polys[i] = polys[(int) (i + 1.f)];
				polys[(int) (i + 1.f)] = tempPoly;
				swaps++;
			}
		}
	}
}
