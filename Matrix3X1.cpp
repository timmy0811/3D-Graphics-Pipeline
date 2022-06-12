#include "Matrix3X1.h"

Matrix3X1::Matrix3X1(float x0, float y0, float z0, float angle = 0.f, MATRIX_TYPE type)
	:Matrix(angle, type), x0(x0), y0(y0), z0(z0)
{

}
