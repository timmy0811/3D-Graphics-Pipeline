#include "Camera.h"

Camera::Camera(sf::Vector3f position, sf::Vector2f rotation)
	:position(position), rotation(rotation)
{
	move(position);
	rotate(rotation);

	globalOffset = sf::Vector3f();
}

void Camera::move(sf::Vector3f direction)
{
	globalOffset += direction;
}

void Camera::rotate(sf::Vector2f angle)
{
	rotation += angle;
}

sf::Vector3f* Camera::getOffset()
{
	return &globalOffset;
}
