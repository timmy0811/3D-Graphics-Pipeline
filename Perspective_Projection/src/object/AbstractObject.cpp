#include "AbstractObject.h"

std::string projection::AbstractObject::getName() const
{
    return name_;
}

sf::Vector3f* projection::AbstractObject::getPositionAbs()
{
    sf::Vector3f* out = new sf::Vector3f(*m_PosX, *m_PosY, *m_PosZ);
    return out;
}

sf::Vector3f* projection::AbstractObject::getRotationAbs()
{
    return &m_RotationAbsolute;
}

sf::Vector3f* projection::AbstractObject::getScaleAbs()
{
    return &m_ScaleAbsolute;
}

void projection::AbstractObject::setName(std::string name)
{
    this->name_ = name;
}

void projection::AbstractObject::setPostion(sf::Vector3f position)
{
    *this->m_PosX = position.x;
    *this->m_PosY = position.y;
    *this->m_PosZ = position.z;
}

void projection::AbstractObject::setRotation(sf::Vector3f rotation)
{
    this->m_RotationAbsolute = rotation;
}

void projection::AbstractObject::setScale(sf::Vector3f scale)
{
    this->m_ScaleAbsolute = scale;
}
