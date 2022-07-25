#pragma once

#include "Matrix3X1.h"

class Matrix3X3 : public Matrix3X1
{	
public:
	// Attributes
	float x1, x2;
	float y1, y2;
	float z1, z2;

	Matrix3X3(float angle = 0, MATRIX_TYPE type = MATRIX_TYPE::DEFAULT, float x0 = 0.f, float x1 = 0.f, float x2 = 0.f, float y0 = 0.f, float y1 = 0.f, float y2 = 0.f, float z0 = 0.f, float z1 = 0.f, float z2 = 0.f);
};

