#include "Cube.h"

void Cube::createVert(float p1, float p2)
{
	sf::Vertex vert1[2] = {
			sf::Vertex(sf::Vector2f(points[p1].getProjMatrix()->x0, points[p1].getProjMatrix()->y0), sf::Color::White),
			sf::Vertex(sf::Vector2f(points[p2].getProjMatrix()->x0, points[p2].getProjMatrix()->y0), sf::Color::White),
	};
	vertices.push_back(vert1);
}

Cube::Cube(sf::Vector2f position, float size)
{
	points.push_back(Point(sf::Vector3f(0.5f, -0.5f, -0.5f)));
	points.push_back(Point(sf::Vector3f(-0.5f, 0.5f, -0.5f)));
	points.push_back(Point(sf::Vector3f(0.5f, 0.5f, -0.5f)));
	points.push_back(Point(sf::Vector3f(-0.5f, -0.5f, -0.5f)));

	points.push_back(Point(sf::Vector3f(0.5f, -0.5f, 0.5f)));
	points.push_back(Point(sf::Vector3f(-0.5f, 0.5f, 0.5f)));
	points.push_back(Point(sf::Vector3f(0.5f, 0.5f, 0.5f)));
	points.push_back(Point(sf::Vector3f(-0.5f, -0.5f, 0.5f)));
}

void Cube::rotateX(float angle)
{
	for (Point p : points) {
		p.rotateX(angle);
	}
}

void Cube::rotateY(float angle)
{
	for (Point p : points) {
		p.rotateY(angle);
	}
}

void Cube::rotateZ(float angle)
{
	for (Point p : points) {
		p.rotateZ(angle);
	}
}

void Cube::connect()
{
	createVert(0, 1);
	createVert(1, 2);
	createVert(2, 3);
	createVert(3, 0);

	createVert(0, 4);
	createVert(1, 5);
	createVert(2, 6);
	createVert(3, 7);

	createVert(4, 5);
	createVert(4, 7);
	createVert(5, 6);
	createVert(5, 7);
}
