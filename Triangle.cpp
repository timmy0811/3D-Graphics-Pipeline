#include "Triangle.h"

Triangle::Triangle(sf::Vector3f pos1, sf::Vector3f pos2, sf::Vector3f pos3, sf::Color color)
{
	p1 = new Point(pos1);
	p2 = new Point(pos2);
	p3 = new Point(pos3);

	p1->setGlobalOffset(globalOffset);
	p2->setGlobalOffset(globalOffset);
	p3->setGlobalOffset(globalOffset);

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
	
	if(calculateProjectedZ() < 0.f) target->draw(vertices[0]);
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

void Triangle::rotateX(float angle, sf::Vector3f refPosition)
{
	p1->rotateX(angle, refPosition);
	p2->rotateX(angle, refPosition);
	p3->rotateX(angle, refPosition);
}

void Triangle::rotateY(float angle, sf::Vector3f refPosition)
{
	p1->rotateY(angle, refPosition);
	p2->rotateY(angle, refPosition);
	p3->rotateY(angle, refPosition);
}

void Triangle::rotateZ(float angle, sf::Vector3f refPosition)
{
	p1->rotateZ(angle, refPosition);
	p2->rotateZ(angle, refPosition);
	p3->rotateZ(angle, refPosition);
}

double Triangle::averageZ()
{
	return (p1->getPosition().z + p2->getPosition().z + p3->getPosition().z) / 3.f;
}

double Triangle::calculateProjectedZ()
{
	sf::Vector3f p1p2 = (p2->getProjPosition() - p1->getProjPosition());
	sf::Vector3f p1p3 = (p3->getProjPosition() - p1->getProjPosition());

	p1p2.z = 0.f;
	p1p3.z = 0.f;

	return p1p2.x * p1p3.y - p1p2.y * p1p3.x;
}

void Triangle::translateToRelative(sf::RenderTarget* target)
{
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
