#include "Camera.h"

Camera::Camera(sf::Vector3f position, sf::Vector2f rotation_)
	:position(position), rotation_(rotation_)
{
	move(position);
	rotate(rotation_);

	globalOffset_ = sf::Vector3f();
}

void Camera::move(sf::Vector3f direction)
{
	globalOffset_ += direction;
}

void Camera::rotate(sf::Vector2f angle)
{
	/*Matrix3X3* rotXMat = new Matrix3X3(angle.x, MATRIX_TYPE::ROTATION_X);
	Matrix3X3* rotYMat = new Matrix3X3(angle.y, MATRIX_TYPE::ROTATION_Y);

	Matrix3X1* offset = new Matrix3X1();
	offset->x0 = globalOffset_.x;
	offset->y0 = globalOffset_.y;
	offset->z0 = globalOffset_.z;

	*offset = maop::matMul(*rotXMat, *offset);
	*offset = maop::matMul(*rotYMat, *offset);

	globalOffset_.x = offset->x0;
	globalOffset_.y = offset->y0;
	globalOffset_.z = offset->z0;

	delete rotXMat;
	delete rotYMat;
	delete offset;

	rotation_ += angle;*/
}

sf::Vector3f* Camera::getOffset()
{
	return &globalOffset_;
}
