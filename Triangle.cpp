#include "Triangle.h"

Triangle::Triangle(sf::Vector3f pos1, sf::Vector3f pos2, sf::Vector3f pos3, sf::Color color)
{
	p1 = new Point(pos1);
	p2 = new Point(pos2);
	p3 = new Point(pos3);

	this->color = color;
}

void Triangle::applyPerspective(float distance)
{
	p1->applyPerspective(distance);
	p2->applyPerspective(distance);
	p3->applyPerspective(distance);
}

void Triangle::render(sf::RenderTarget* target)
{
	createPoly(target);

	target->draw(vertices[0]);
}

void Triangle::rotateX(float angle)
{
	p1->rotateX(angle);
	p2->rotateX(angle);
	p3->rotateX(angle);
}

void Triangle::rotateY(float angle)
{
	p1->rotateY(angle);
	p2->rotateY(angle);
	p3->rotateY(angle);
}

void Triangle::rotateZ(float angle)
{
	p1->rotateZ(angle);
	p2->rotateZ(angle);
	p3->rotateZ(angle);
}

void Triangle::createPoly(sf::RenderTarget* target)
{
	vertices.clear();

	sf::VertexArray poly(sf::Triangles, 3);
	poly[0].position = translateToRel(sf::Vector2f(p1->getProjMatrix()->x0, p1->getProjMatrix()->y0), target->getSize().x);
	poly[1].position = translateToRel(sf::Vector2f(p2->getProjMatrix()->x0, p2->getProjMatrix()->y0), target->getSize().x);
	poly[2].position = translateToRel(sf::Vector2f(p3->getProjMatrix()->x0, p3->getProjMatrix()->y0), target->getSize().x);


	poly[0].color = color;
	poly[1].color = color;
	poly[2].color = color;

	vertices.push_back(poly);
}
