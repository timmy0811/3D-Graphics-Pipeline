#include "Point.h"

Point::Point(sf::Vector3f position)
{
	this->position = Matrix3X1(0.f, MATRIX_TYPE::PROJECTION, position.x, position.y, position.z);

	this->shape = sf::CircleShape(5.f);
	shape.setFillColor(sf::Color::White);
}

void Point::render(sf::RenderTarget* target)
{
	sf::Vector2f pos = translateToRel(sf::Vector2f(projectedPositon.x0, projectedPositon.y0), target->getSize().x);
	shape.setPosition(sf::Vector2f(pos.x - 2.5f, pos.y - 2.5f));
	target->draw(shape);
}

void Point::applyPerspective(float distance)
{
	projectedPositon.x0 = position.x0 / (distance - position.z0);
	projectedPositon.y0 = position.y0 / (distance - position.z0);
	projectedPositon.z0 = position.z0;
}

void Point::setMatrix(Matrix3X1 mat)
{
	this->position = mat;
}

Matrix3X1* Point::getMatrix()
{
	return &(this->position);
}

void Point::setProjMatrix(Matrix3X1 mat)
{
	this->projectedPositon = mat;
}

Matrix3X1* Point::getProjMatrix()
{
	return &(this->projectedPositon);
}

sf::Vector3f Point::getPosition()
{
	return sf::Vector3f(position.x0, position.y0, position.z0);
}

sf::Vector3f Point::getProjPosition()
{
	return sf::Vector3f(projectedPositon.x0, projectedPositon.y0, projectedPositon.z0);
}

void Point::rotateX(float angle)
{
	Matrix3X3* mat = new Matrix3X3(angle, MATRIX_TYPE::ROTATION_X);
	position = maop::matMul(*mat, position);
	delete mat;
}

void Point::rotateY(float angle)
{
	Matrix3X3* mat = new Matrix3X3(angle, MATRIX_TYPE::ROTATION_Y);
	position = maop::matMul(*mat, position);
	delete mat;
}

void Point::rotateZ(float angle)
{
	Matrix3X3* mat = new Matrix3X3(angle, MATRIX_TYPE::ROTATION_Z);
	position = maop::matMul(*mat, position);
	delete mat;
}

std::vector<Point*>* Point::getPoints()
{
	std::vector<Point*> pList;
	pList.push_back(this);
	return &pList;
}
