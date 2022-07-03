#include "Cube.h"

Cube::Cube(sf::Vector3f position, float size, sf::Color color, sf::RenderTarget* target, bool wireFrame)
{
	this->wireFrame = wireFrame;
	this->color = color;
	this->target = target;

	meshCenter.x0 = position.x + size / 2.f;
	meshCenter.y0 = position.y + size / 2.f;
	meshCenter.z0 = position.z + size / 2.f;

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, 0.f	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, 0.f	+ position.z)));

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, size	+ position.z)));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, size	+ position.z)));

	for (Point* point : points) {
		point->setGlobalOffset(globalOffset);
	}
}

Cube::~Cube()
{
	Mesh::~Mesh();
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

		createTriangle(points[3], points[2], points[1], sf::Color::Blue);
		createTriangle(points[0], points[2], points[3], sf::Color::Blue);

		createTriangle(points[7], points[5], points[6], sf::Color::Red);
		createTriangle(points[4], points[7], points[6], sf::Color::Red);

		createTriangle(points[3], points[7], points[4], sf::Color::Yellow);
		createTriangle(points[0], points[3], points[4], sf::Color::Yellow);

		createTriangle(points[5], points[3], points[1], sf::Color::Green);
		createTriangle(points[7], points[3], points[5], sf::Color::Green);

		createTriangle(points[5], points[1], points[6], sf::Color::Magenta);
		createTriangle(points[1], points[2], points[6], sf::Color::Magenta);

		createTriangle(points[0], points[4], points[6], sf::Color::White);
		createTriangle(points[2], points[0], points[6], sf::Color::White);
	}
}
