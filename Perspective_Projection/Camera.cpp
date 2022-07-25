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
	rotation_ += angle;
}

sf::Vector3f* Camera::getOffset()
{
	return &globalOffset_;
}
