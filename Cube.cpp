#include "Cube.h"

void Cube::createVert(int p1, int p2, sf::RenderTarget* target)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = translateToRel(sf::Vector2f(points[p1]->getProjMatrix()->x0, points[p1]->getProjMatrix()->y0), target->getSize().x);
	line[1].position = translateToRel(sf::Vector2f(points[p2]->getProjMatrix()->x0, points[p2]->getProjMatrix()->y0), target->getSize().x);

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	vertices.push_back(line);
}

Cube::Cube(sf::Vector2f position, float size)
{
	points.push_back(new Point(sf::Vector3f(size, -size, -size)));
	points.push_back(new Point(sf::Vector3f(-size, size, -size)));
	points.push_back(new Point(sf::Vector3f(size, size, -size)));
	points.push_back(new Point(sf::Vector3f(-size, -size, -size)));

	points.push_back(new Point(sf::Vector3f(size, -size, size)));
	points.push_back(new Point(sf::Vector3f(-size, size, size)));
	points.push_back(new Point(sf::Vector3f(size, size, size)));
	points.push_back(new Point(sf::Vector3f(-size, -size, size)));
}

void Cube::render(sf::RenderTarget* target)
{
	connect(target);

	for (Point* p : points) {
		p->render(target);
	}

	for (int i = 0; i < vertices.size(); i++) {
		target->draw(vertices[i]);
	}
}

void Cube::applyPerspective(float distance)
{
	for (Point* p : points) {
		p->applyPerspective(distance);
	}
}

void Cube::rotateX(float angle)
{
	for (Point* p : points) {
		p->rotateX(angle);
	}
}

void Cube::rotateY(float angle)
{
	for (Point* p : points) {
		p->rotateY(angle);
	}
}

void Cube::rotateZ(float angle)
{
	for (Point* p : points) {
		p->rotateZ(angle);
	}
}

void Cube::connect(sf::RenderTarget* target)
{
	vertices.clear();

	createVert(0, 1, target);
	createVert(1, 2, target);
	createVert(2, 3, target);
	createVert(3, 0, target);

	createVert(0, 4, target);
	createVert(1, 5, target);
	createVert(2, 6, target);
	createVert(3, 7, target);

	createVert(4, 5, target);
	createVert(4, 7, target);
	createVert(5, 6, target);
	createVert(5, 7, target);
}

std::vector<Point*>* Cube::getPoints()
{
	return &points;
}
