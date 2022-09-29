#include "Point.h"

projection::Point::Point(sf::Vector3f position, std::string name, Matrix3X1* parentPos)
{
	m_W = 1.f;
	name_ = name;

	this->m_Position = Matrix3X1(0.f, MATRIX_TYPE::PROJECTION, position.x, position.y, position.z);
	/*posX = &this->position.x0;
	posY = &this->position.y0;
	posZ = &this->position.z0;*/

	this->m_Shape = sf::CircleShape(5.f);
	m_Shape.setFillColor(sf::Color::White);
}

void projection::Point::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	if (m_Position.z0 + m_GlobalOffset->z > c_z_clipping) return;
	sf::Vector2f pos = translateToRel(sf::Vector2f(m_PositionProjected.x0, m_PositionProjected.y0), target->getSize());
	m_Shape.setPosition(sf::Vector2f(pos.x - 2.5f, pos.y - 2.5f));
	target->draw(m_Shape);
}

void projection::Point::applyPerspective()
{
	m_PositionProjected.x0 = (m_Position.x0 + m_GlobalOffset->x) * c_viewPortDistance / (c_viewPortDistance + m_Position.z0 + m_GlobalOffset->z);
	m_PositionProjected.y0 = (m_Position.y0 + m_GlobalOffset->y) * c_viewPortDistance / (c_viewPortDistance + m_Position.z0 + m_GlobalOffset->z);
	m_PositionProjected.z0 = (m_Position.z0 + m_GlobalOffset->z);

	// offset?
	m_wProjected = m_W * c_viewPortDistance / (c_viewPortDistance + m_Position.z0 + m_GlobalOffset->z);
}

void projection::Point::moveByValue(sf::Vector3f dir)
{
	m_Position.x0 += dir.x;
	m_Position.y0 += dir.y;
	m_Position.z0 += dir.z;
}

void projection::Point::moveToPos(sf::Vector3f pos)
{
	m_Position.x0 = pos.x;
	m_Position.y0 = pos.y;
	m_Position.z0 = pos.z;
}

void projection::Point::setMatrix(Matrix3X1 mat)
{
	this->m_Position = mat;
}

Matrix3X1* projection::Point::getMatrix()
{
	return &(this->m_Position);
}

void projection::Point::setProjMatrix(Matrix3X1 mat)
{
	this->m_PositionProjected = mat;
}

Matrix3X1* projection::Point::getProjMatrix()
{
	return &(this->m_PositionProjected);
}

sf::Vector3f projection::Point::getPosition()
{
	return sf::Vector3f(m_Position.x0, m_Position.y0, m_Position.z0);
}

sf::Vector3f projection::Point::getProjPosition()
{
	return sf::Vector3f(m_PositionProjected.x0, m_PositionProjected.y0, m_PositionProjected.z0);
}

float projection::Point::getW()
{
	return m_wProjected;
}

sf::Vector2f projection::Point::getScreenPosition(sf::RenderTarget* target)
{
	return translateToRel(sf::Vector2f(m_PositionProjected.x0, m_PositionProjected.y0), target->getSize());
}

void projection::Point::rotateX(float angle)
{
	return;
}

void projection::Point::rotateY(float angle)
{
	return;
}

void projection::Point::rotateZ(float angle)
{
	return;
}

void projection::Point::rotateX(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_X);
}

void projection::Point::rotateY(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Y);
}

void projection::Point::rotateZ(float angle, sf::Vector3f refPosition)
{
	rotateByEnum(angle, refPosition, MATRIX_TYPE::ROTATION_Z);
}

void projection::Point::rotateByCamera(float angle, sf::Vector3f refPosition)
{
	rotateY(angle, refPosition);
}

void projection::Point::rotateByEnum(float angle, sf::Vector3f refPosition, MATRIX_TYPE type)
{
	Matrix3X1* relPos = new Matrix3X1();
	relPos->x0 = refPosition.x - m_Position.x0;
	relPos->y0 = refPosition.y - m_Position.y0;
	relPos->z0 = refPosition.z - m_Position.z0;

	Matrix3X3* mat = new Matrix3X3(angle, type);
	Matrix3X1 deltaPos = maop::matMul(*mat, *relPos);

	m_Position.x0 += relPos->x0 - deltaPos.x0;
	m_Position.y0 += relPos->y0 - deltaPos.y0;
	m_Position.z0 += relPos->z0 - deltaPos.z0;

	//Matrix3X1* ptrPos = &deltaPos;
	//delete ptrPos;
	delete relPos;
	delete mat;
}

std::vector<projection::Point*>* projection::Point::getPoints()
{
	std::vector<Point*> pList;
	pList.push_back(this);
	return &pList;
}

float projection::Point::applyPerspCorr(float v)
{
	return v * c_viewPortDistance / (c_viewPortDistance + m_Position.z0 + m_GlobalOffset->z);
}
