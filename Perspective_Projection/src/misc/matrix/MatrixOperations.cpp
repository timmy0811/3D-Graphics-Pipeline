#include "MatrixOperations.h"

Matrix3X1 maop::matMul(Matrix3X3 m1, Matrix3X1 m2)
{
	Matrix3X1 matRet = Matrix3X1();

	matRet.x0 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.y0 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.z0 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;

	return matRet;
}

Matrix3X3 maop::matMul(Matrix3X3 m1, Matrix3X3 m2)
{
	Matrix3X3 matRet = Matrix3X3();

	matRet.x0 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.x1 = m1.x0 * m2.x1 + m1.x1 * m2.y1 + m1.x2 * m2.z1;
	matRet.x2 = m1.x0 * m2.x2 + m1.x1 * m2.y2 + m1.x2 * m2.z2;

	matRet.y0 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.y1 = m1.y0 * m2.x1 + m1.y1 * m2.y1 + m1.y2 * m2.z1;
	matRet.y2 = m1.y0 * m2.x2 + m1.y1 * m2.y2 + m1.y2 * m2.z2;

	matRet.z0 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;
	matRet.z1 = m1.z0 * m2.x1 + m1.z1 * m2.y1 + m1.z2 * m2.z1;
	matRet.z2 = m1.z0 * m2.x2 + m1.z1 * m2.y2 + m1.z2 * m2.z2;

	return matRet;
}

Matrix3X3 maop::matAdd(Matrix3X3 m1, Matrix3X3 m2)
{
	Matrix3X3 matRet = Matrix3X3();

	matRet.x0 = m1.x0 + m2.x0;
	matRet.x1 = m1.x1 + m2.x1;
	matRet.x2 = m1.x2 + m2.x2;

	matRet.y0 = m1.y0 + m2.y0;
	matRet.y1 = m1.y1 + m2.y1;
	matRet.y2 = m1.y2 + m2.y2;

	matRet.z0 = m1.z0 + m2.z0;
	matRet.z1 = m1.z1 + m2.z1;
	matRet.z2 = m1.z2 + m2.z2;

	return matRet;
}

Matrix3X1 maop::matAdd(Matrix3X1 m1, Matrix3X1 m2)
{
	Matrix3X1 matRet = Matrix3X3();

	matRet.x0 = m1.x0 + m2.x0;
	matRet.y0 = m1.y0 + m2.y0;
	matRet.z0 = m1.z0 + m2.z0;

	return matRet;
}

Matrix3X3 maop::matSub(Matrix3X3 m1, Matrix3X3 m2)
{
	Matrix3X3 matRet = Matrix3X3();

	matRet.x0 = m1.x0 - m2.x0;
	matRet.x1 = m1.x1 - m2.x1;
	matRet.x2 = m1.x2 - m2.x2;

	matRet.y0 = m1.y0 - m2.y0;
	matRet.y1 = m1.y1 - m2.y1;
	matRet.y2 = m1.y2 - m2.y2;

	matRet.z0 = m1.z0 - m2.z0;
	matRet.z1 = m1.z1 - m2.z1;
	matRet.z2 = m1.z2 - m2.z2;

	return matRet;
}

Matrix3X1 maop::matSub(Matrix3X1 m1, Matrix3X1 m2)
{
	Matrix3X1 matRet = Matrix3X1();

	matRet.x0 = m1.x0 - m2.x0;
	matRet.y0 = m1.y0 - m2.y0;
	matRet.z0 = m1.z0 - m2.z0;

	return matRet;
}

sf::Vector3f maop::matToVec(Matrix3X1* mat)
{
	sf::Vector3f vec;
	vec.x = mat->x0;
	vec.y = mat->y0;
	vec.z = mat->z0;

	return vec;
}
