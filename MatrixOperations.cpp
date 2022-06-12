#include "MatrixOperations.h"

Matrix3X1 MatrixOperations::matMul(Matrix3X3 m1, Matrix3X1 m2)
{
	Matrix3X1 matRet = Matrix3X1();

	matRet.x0 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.y0 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.z0 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;

	return matRet;
}

Matrix3X3 MatrixOperations::matMul(Matrix3X3 m1, Matrix3X3 m2)
{
	Matrix3X3 matRet = Matrix3X3();

	matRet.x0 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.x1 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.x2 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;

	matRet.x1 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.y0 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.z0 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;

	matRet.x0 = m1.x0 * m2.x0 + m1.x1 * m2.y0 + m1.x2 * m2.z0;
	matRet.y0 = m1.y0 * m2.x0 + m1.y1 * m2.y0 + m1.y2 * m2.z0;
	matRet.z0 = m1.z0 * m2.x0 + m1.z1 * m2.y0 + m1.z2 * m2.z0;

	return matRet;
}
