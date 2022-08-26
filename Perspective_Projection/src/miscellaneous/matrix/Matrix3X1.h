#pragma once

#include "Matrix.h"

class Matrix3X1 : public Matrix
{
public:
	// Attributes
	float x0, y0, z0;

	Matrix3X1(float angle = 0.f, MATRIX_TYPE type = MATRIX_TYPE::DEFAULT, float x0 = 0.f, float y0 = 0.f, float z0 = 0.f);
};

