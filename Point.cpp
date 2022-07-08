#include "Point.h"

Point::Point(sf::Vector3f position, Matrix3X1* parentPos)
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

void Point::applyPerspective(float distance_)
{
	projectedPositon.x0 = (position.x0 + globalOffset_->x) / (distance_ - (position.z0 + globalOffset_->z));
	projectedPositon.y0 = (position.y0 + globalOffset_->y) / (distance_ - (position.z0+ globalOffset_->z));
	projectedPositon.z0 = position.z0 + globalOffset_->z;
}

void Point::moveByValue(sf::Vector3f dir)
{
	position.x0 += dir.x;
	position.y0 += dir.y;
	position.z0 += dir.z;
}

void Point::moveToPos(sf::Vector3f pos)
{
	position.x0 = pos.x;
	position.y0 = pos.y;
	position.z0 = pos.z;
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
	return;
}

void Point::rotateY(float angle)
{
	return;
}

void Point::rotateZ(float angle)
{
	return;
}

void Point::rotateX(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_X);
}

void Point::rotateY(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Y);
}

void Point::rotateZ(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Z);
}

void Point::rotateByEnum(float angle, sf::Vector3f refPosition, MATRIX_TYPE type)
{
	Matrix3X1* relPos = new Matrix3X1();
	relPos->x0 = refPosition.x - position.x0;
	relPos->y0 = refPosition.y - position.y0;
	relPos->z0 = refPosition.z - position.z0;

	Matrix3X3* mat = new Matrix3X3(angle, type);
	Matrix3X1 deltaPos = maop::matMul(*mat, *relPos);

	position.x0 += relPos->x0 - deltaPos.x0;
	position.y0 += relPos->y0 - deltaPos.y0;
	position.z0 += relPos->z0 - deltaPos.z0;

	//Matrix3X1* ptrPos = &deltaPos;
	//delete ptrPos;
	delete relPos;
	delete mat;
}

std::vector<Point*>* Point::getPoints()
{
	std::vector<Point*> pList;
	pList.push_back(this);
	return &pList;
}
