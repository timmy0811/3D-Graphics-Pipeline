#include "Matrix.h"

Matrix::Matrix(float angle, MATRIX_TYPE type)
	:type(type), angle(angle)
{
}

float Matrix::getAngle()
{
	return angle;
}

void Matrix::setAngle(float angle)
{
	this->angle = angle;
}

void Matrix::addAngle(float amount)
{
	this->angle += amount;
}
