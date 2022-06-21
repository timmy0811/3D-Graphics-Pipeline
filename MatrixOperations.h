#pragma once

#include "Matrix.h"
#include "Matrix3X1.h"
#include "Matrix3X3.h"

namespace maop
{
	Matrix3X1 matMul(Matrix3X3 m1, Matrix3X1 m2);
	Matrix3X3 matMul(Matrix3X3 m1, Matrix3X3 m2);
	
	Matrix3X3 matAdd(Matrix3X3 m1, Matrix3X3 m2);
	Matrix3X1 matAdd(Matrix3X1 m1, Matrix3X1 m2);

	Matrix3X3 matSub(Matrix3X3 m1, Matrix3X3 m2);
	Matrix3X1 matSub(Matrix3X1 m1, Matrix3X1 m2);
};

