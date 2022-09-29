#include "Camera.h"

projection::Camera::Camera(sf::Vector3f position, sf::Vector2f rotation_)
	:m_Position(position), m_Rotation(rotation_)
{
	move(position);
	//rotate(rotation_);
	this->m_Position = { 0.f, 0.f, (float)c_viewPortDistance };

	m_GlobalOffset = sf::Vector3f();
}

void projection::Camera::move(sf::Vector3f direction)
{
	m_GlobalOffset += direction;
}

void projection::Camera::rotate(sf::Vector2f angle , std::vector<Renderable*> sceneObjects)
{
	this->m_Position = { -m_GlobalOffset.x, -m_GlobalOffset.y, -(float)c_viewPortDistance - m_GlobalOffset.z };

	for (Renderable* obj : sceneObjects) {
		obj->rotateByCamera(angle.x, m_Position);
	}

	this->m_Rotation += angle;

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

sf::Vector3f* projection::Camera::getOffset()
{
	return &m_GlobalOffset;
}
