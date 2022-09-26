#include "Point.h"

projection::Point::Point(sf::Vector3f position, std::string name, Matrix3X1* parentPos)
{
	w = 1.f;
	name_ = name;

	this->position = Matrix3X1(0.f, MATRIX_TYPE::PROJECTION, position.x, position.y, position.z);
	/*posX = &this->position.x0;
	posY = &this->position.y0;
	posZ = &this->position.z0;*/

	this->shape = sf::CircleShape(5.f);
	shape.setFillColor(sf::Color::White);
}

void projection::Point::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	if (position.z0 + globalOffset_->z > c_z_clipping) return;
	sf::Vector2f pos = translateToRel(sf::Vector2f(projectedPositon.x0, projectedPositon.y0), target->getSize());
	shape.setPosition(sf::Vector2f(pos.x - 2.5f, pos.y - 2.5f));
	target->draw(shape);
}

void projection::Point::applyPerspective()
{
	projectedPositon.x0 = (position.x0 + globalOffset_->x) * c_viewPortDistance / (c_viewPortDistance + position.z0 + globalOffset_->z);
	projectedPositon.y0 = (position.y0 + globalOffset_->y) * c_viewPortDistance / (c_viewPortDistance + position.z0 + globalOffset_->z);
	projectedPositon.z0 = (position.z0 + globalOffset_->z);

	// offset?
	wProj = w * c_viewPortDistance / (c_viewPortDistance + position.z0 + globalOffset_->z);
}

void projection::Point::moveByValue(sf::Vector3f dir)
{
	position.x0 += dir.x;
	position.y0 += dir.y;
	position.z0 += dir.z;
}

void projection::Point::moveToPos(sf::Vector3f pos)
{
	position.x0 = pos.x;
	position.y0 = pos.y;
	position.z0 = pos.z;
}

void projection::Point::setMatrix(Matrix3X1 mat)
{
	this->position = mat;
}

Matrix3X1* projection::Point::getMatrix()
{
	return &(this->position);
}

void projection::Point::setProjMatrix(Matrix3X1 mat)
{
	this->projectedPositon = mat;
}

Matrix3X1* projection::Point::getProjMatrix()
{
	return &(this->projectedPositon);
}

sf::Vector3f projection::Point::getPosition()
{
	return sf::Vector3f(position.x0, position.y0, position.z0);
}

sf::Vector3f projection::Point::getProjPosition()
{
	return sf::Vector3f(projectedPositon.x0, projectedPositon.y0, projectedPositon.z0);
}

float projection::Point::getW()
{
	return wProj;
}

sf::Vector2f projection::Point::getScreenPosition(sf::RenderTarget* target)
{
	return translateToRel(sf::Vector2f(projectedPositon.x0, projectedPositon.y0), target->getSize());
}

void projection::Point::rotateX(float angle)
{
	return;
}

void projection::Point::rotateY(float angle)
{
	return;
}

void projection::Point::rotateZ(float angle)
{
	return;
}

void projection::Point::rotateX(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_X);
}

void projection::Point::rotateY(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Y);
}

void projection::Point::rotateZ(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Z);
}

void projection::Point::rotateByCamera(float angle, sf::Vector3f refPosition)
{
	rotateY(angle, refPosition);
}

void projection::Point::rotateByEnum(float angle, sf::Vector3f refPosition, MATRIX_TYPE type)
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

std::vector<projection::Point*>* projection::Point::getPoints()
{
	std::vector<Point*> pList;
	pList.push_back(this);
	return &pList;
}

float projection::Point::applyPerspCorr(float v)
{
	return v * c_viewPortDistance / (c_viewPortDistance + position.z0 + globalOffset_->z);
}
