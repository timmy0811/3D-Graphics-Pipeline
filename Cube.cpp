#include "Cube.h"

Cube::Cube(sf::Vector3f position, float size, sf::Color color, sf::RenderTarget* target, std::string name, bool wireFrame_)
{
	name_ = name;

	this->wireFrame_ = wireFrame_;
	this->color = color;
	this->target = target;

	meshCenter.x0 = position.x + size / 2.f;
	meshCenter.y0 = position.y + size / 2.f;
	meshCenter.z0 = position.z + size / 2.f;

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, 0.f	+ position.z), "point_0"));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, 0.f	+ position.z), "point_1"));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, 0.f	+ position.z), "point_2"));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, 0.f	+ position.z), "point_3"));

	points.push_back(new Point(sf::Vector3f(size	+ position.x, 0.f	+ position.y, size	+ position.z), "point_4"));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, size	+ position.y, size	+ position.z), "point_5"));
	points.push_back(new Point(sf::Vector3f(size	+ position.x, size	+ position.y, size	+ position.z), "point_6"));
	points.push_back(new Point(sf::Vector3f(0.f		+ position.x, 0.f	+ position.y, size	+ position.z), "point_7"));
}

Cube::~Cube()
{
	Mesh::~Mesh();
}

void Cube::connect(sf::RenderTarget* target)
{
	if (wireFrame_) {
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
		for (Triangle* poly : polys) {
			delete poly;
		}

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
