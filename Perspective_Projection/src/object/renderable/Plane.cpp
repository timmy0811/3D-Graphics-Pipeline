#include "Plane.h"

projection::Plane::Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, sf::Color color)
{
	isTextured = false;
	name_ = name;
	this->target = target;
	this->color = color;

	meshCenter.x0 = position.x + size.x / 2.f;
	meshCenter.y0 = position.y;
	meshCenter.z0 = position.z + size.y / 2.f;

	scaleAbs.x = size.x;
	scaleAbs.y = 0.f;
	scaleAbs.z = size.y;

	posX = &position.x;
	posY = &position.y;
	posZ = &position.z;

	points.push_back(new Point(sf::Vector3f(position.x, position.y,position.z), "point_0"));
	points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z), "point_1"));
	points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z + size.y), "point_2"));
	points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z + size.y), "point_3"));
}

projection::Plane::Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, Texture* texture)
{
	isTextured = true;
	name_ = name;
	this->target = target;
	this->texture = texture;
	this->color = color;

	meshCenter.x0 = position.x + size.x / 2.f;
	meshCenter.y0 = position.y;
	meshCenter.z0 = position.z + size.y / 2.f;

	scaleAbs.x = size.x;
	scaleAbs.y = 0.f;
	scaleAbs.z = size.y;

	posX = &position.x;
	posY = &position.y;
	posZ = &position.z;

	points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z), "point_0"));
	points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z), "point_1"));
	points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z + size.y), "point_2"));
	points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z + size.y), "point_3"));
}

projection::Plane::~Plane()
{
	Mesh::~Mesh();
}

void projection::Plane::connect(sf::RenderTarget* target)
{
	for (Triangle* poly : polys) {
		delete poly;
	}

	polys.clear();

	if (isTextured) {
		createTriangle(points[0], points[3], points[1], sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(points[3], points[2], points[1], sf::Vector2f(1.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 1.f));
	}
	else {
		createTriangle(points[0], points[3], points[1], color);
		createTriangle(points[3], points[2], points[1], color);
	}
}
