#include "Cube.h"

void Cube::init(sf::Vector3f position, float size)
{
	meshCenter.x0 = position.x + size / 2.f;
	meshCenter.y0 = position.y + size / 2.f;
	meshCenter.z0 = position.z + size / 2.f;

	points.push_back(new Point(sf::Vector3f(size + position.x, 0.f + position.y, 0.f + position.z), "point_0"));
	points.push_back(new Point(sf::Vector3f(0.f + position.x, size + position.y, 0.f + position.z), "point_1"));
	points.push_back(new Point(sf::Vector3f(size + position.x, size + position.y, 0.f + position.z), "point_2"));
	points.push_back(new Point(sf::Vector3f(0.f + position.x, 0.f + position.y, 0.f + position.z), "point_3"));

	points.push_back(new Point(sf::Vector3f(size + position.x, 0.0f + position.y, size + position.z), "point_4"));
	points.push_back(new Point(sf::Vector3f(0.f + position.x, size + position.y, size + position.z), "point_5"));
	points.push_back(new Point(sf::Vector3f(size + position.x, size + position.y, size + position.z), "point_6"));
	points.push_back(new Point(sf::Vector3f(0.f + position.x, 0.f + position.y, size + position.z), "point_7"));

	posX = new float;
	posY = new float;
	posZ = new float;

	*posX = position.x;
	*posY = position.x;
	*posZ = position.x;
}

Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name)
{
	isTextured = false;
	wireFrame_ = true;
	name_ = name;
	this->target = target;

	init(position, size);
}

Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, sf::Color color)
{
	isTextured = false;
	wireFrame_ = false;
	this->color = color;
	name_ = name;
	this->target = target;

	init(position, size);
}

Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, Texture* texture)
{
	isTextured = true;
	wireFrame_ = false;
	this->texture = texture;
	name_ = name;
	this->target = target;

	init(position, size);
}

Cube::~Cube()
{
	Mesh::~Mesh();
}

void Cube::connect(sf::RenderTarget* target)
{
	for (Triangle* poly : polys) {
		delete poly;
	}

	polys.clear();

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
	else if(isTextured) {
		createTriangle(points[3], points[2], points[1], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(points[0], points[2], points[3], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(points[7], points[5], points[6], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(points[4], points[7], points[6], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));

		createTriangle(points[3], points[7], points[4], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(points[0], points[3], points[4], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));

		createTriangle(points[5], points[3], points[1], sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(points[7], points[3], points[5], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f));

		createTriangle(points[5], points[1], points[6], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));
		createTriangle(points[1], points[2], points[6], sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(points[0], points[4], points[6], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(points[2], points[0], points[6], sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f));
	}
	else {
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
