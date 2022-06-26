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

Cube::Cube(sf::Vector3f position, float size, sf::Color color, bool wireFrame)
	:wireFrame(wireFrame)
{
	this->color = color;

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, 0.f	+ position.z)));

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, size	+ position.z)));
}

Cube::~Cube()
{
	for (Point* p : points) {
		delete p;
	}
}

void Cube::render(sf::RenderTarget* target)
{
	connect(target);

	for (Point* p : points) {
		//p->render(target);
	}

	for (int i = 0; i < vertices.size(); i++) {
		target->draw(vertices[i]);
	}

	for (Triangle* poly : polys) {
		poly->render(target);
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
	if (wireFrame) {
		vertices.clear();

		createVert(1, 3, target);
		createVert(1, 2, target);
		createVert(2, 0, target);
		createVert(3, 0, target);

		createVert(3, 7, target);
		createVert(0, 4, target);
		createVert(2, 6, target);
		createVert(1, 5, target);

		createVert(7, 4, target);
		createVert(7, 5, target);
		createVert(5, 6, target);
		createVert(6, 4, target);
	}
	else {
		polys.clear();

		createTriangle(points[1], points[3], points[2], color);
		createTriangle(points[0], points[2], points[3], color);

		createTriangle(points[7], points[5], points[6], color);
		createTriangle(points[7], points[4], points[6], color);

		createTriangle(points[3], points[7], points[4], color);
		createTriangle(points[3], points[0], points[4], color);

		createTriangle(points[3], points[1], points[5], color);
		createTriangle(points[3], points[7], points[5], color);

		createTriangle(points[1], points[5], points[6], color);
		createTriangle(points[1], points[2], points[6], color);

		createTriangle(points[0], points[4], points[6], color);
		createTriangle(points[0], points[2], points[6], color);
	}
	
}

std::vector<Point*>* Cube::getPoints()
{
	return &points;
}
