#pragma once

#include <SFML/Graphics.hpp>

enum class MATRIX_TYPE { DEFAULT, ROTATION_X, ROTATION_Y, ROTATION_Z, PROJECTION };

class Matrix
{
protected:
	MATRIX_TYPE type;
	float angle;

public:
	Matrix(float angle = 0.f, MATRIX_TYPE type = MATRIX_TYPE::DEFAULT);
};

