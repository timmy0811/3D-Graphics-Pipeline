#include "Point.h"

Point::Point(sf::Vector3f position, std::string name, Matrix3X1* parentPos, bool screenDim)
	:screenDim(screenDim)
{
	w = 1.f;
	name_ = name;

	this->position = Matrix3X1(0.f, MATRIX_TYPE::PROJECTION, position.x, position.y, position.z);
	posX = &this->position.x0;
	posY = &this->position.y0;
	posZ = &this->position.z0;

	this->shape = sf::CircleShape(5.f);
	shape.setFillColor(sf::Color::White);
}

void Point::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	sf::Vector2f pos;
	if (screenDim) pos = sf::Vector2f(position.x0, position.y0);
	else pos = translateToRel(sf::Vector2f(projectedPositon.x0, projectedPositon.y0), target->getSize());
	shape.setPosition(sf::Vector2f(pos.x - 2.5f, pos.y - 2.5f));
	target->draw(shape);
}

void Point::applyPerspective()
{
	/*projectedPositon.x0 = (position.x0 + globalOffset_->x) / (distance_ - (position.z0 + globalOffset_->z));
	projectedPositon.y0 = (position.y0 + globalOffset_->y) / (distance_ - (position.z0+ globalOffset_->z));
	projectedPositon.z0 = position.z0 + globalOffset_->z;*/

	projectedPositon.x0 = (position.x0 + globalOffset_->x) * (float)c_viewPortDistance / ((float)c_viewPortDistance + position.z0 + globalOffset_->z);
	projectedPositon.y0 = (position.y0 + globalOffset_->y) * (float)c_viewPortDistance / ((float)c_viewPortDistance + position.z0 + globalOffset_->z);
	projectedPositon.z0 = (position.z0 + globalOffset_->z);

	// offset?
	wProj = w * c_viewPortDistance / (c_viewPortDistance + position.z0 + globalOffset_->z);
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

sf::Vector3f Point::convertToScreenCoordinates(sf::RenderTarget* target)
{
	return sf::Vector3f(getScreenPosition(target).x, getScreenPosition(target).y, 0.f);
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
	if(screenDim) return sf::Vector3f(position.x0, position.y0, position.z0);
	return sf::Vector3f(projectedPositon.x0, projectedPositon.y0, projectedPositon.z0);
}

float Point::getW()
{
	return wProj;
}

sf::Vector2f Point::getScreenPosition(sf::RenderTarget* target)
{
	if (screenDim) return sf::Vector2f(position.x0, position.y0);
	else return translateToRel(sf::Vector2f(projectedPositon.x0, projectedPositon.y0), target->getSize());
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

float Point::applyPerspCorr(float v)
{
	return v * (float)c_viewPortDistance / ((float)c_viewPortDistance + position.z0 + globalOffset_->z);
}
