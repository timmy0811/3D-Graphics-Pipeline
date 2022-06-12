#include "Matrix3X3.h"

Matrix3X3::Matrix3X3(float x0, float x1, float x2, float y0, float y1, float y2, float z0, float z1, float z2, float angle, MATRIX_TYPE type)
	:Matrix3X1(x0, y0, z0, angle, type), x1(x0), x2(x2), y1(y1), y2(y2), z1(z0), z2(z2)
{
	switch (type) {
	case MATRIX_TYPE::ROTATION_X: {
		this->x0 = 1.f;
		this->x1 = 0.f;
		this->x2 = 0.f;

		this->y0 = 0.f;
		this->y1 = cos(angle);
		this->y2 = sin(angle);

		this->z0 = 0.f;
		this->z1 = -sin(angle);
		this->z2 = cos(angle);

		break;
	}
	case MATRIX_TYPE::ROTATION_Y: {
		this->x0 = cos(angle);
		this->x1 = 0.f;
		this->x2 = -sin(angle);

		this->y0 = 0.f;
		this->y1 = 1.f;
		this->y2 = 0.f;

		this->z0 = sin(angle);
		this->z1 = 0.f;
		this->z2 = cos(angle);

		break;
	}
	case MATRIX_TYPE::ROTATION_Z: {
		this->x0 = cos(angle);
		this->x1 = sin(angle);
		this->x2 = 0.f;

		this->y0 = -sin(angle);
		this->y1 = cos(angle);
		this->y2 = 0.f;

		this->z0 = 0.f;
		this->z1 = 0.f;
		this->z2 = 1.f;

		break;
	}
	case MATRIX_TYPE::PROJECTION: {
		this->x0 = 1.f;
		this->x1 = 0.f;
		this->x2 = 0.f;

		this->y0 = 0.f;
		this->y1 = 1.f;
		this->y2 = 0.f;

		this->z0 = 0.f;
		this->z1 = 0.f;
		this->z2 = 1.f;

		break;
	}
	case MATRIX_TYPE::DEFAULT: {
		this->x0 = 0.f;
		this->x1 = 0.f;
		this->x2 = 0.f;

		this->y0 = 0.f;
		this->y1 = 0.f;
		this->y2 = 0.f;

		this->z0 = 0.f;
		this->z1 = 0.f;
		this->z2 = 0.f;

		break;
	}
	default:
		throw std::invalid_argument("must set matrix type");
	}
}
