#include "AbstractObject.h"

std::string projection::AbstractObject::getName()
{
    return name_;
}

sf::Vector3f* projection::AbstractObject::getPositionAbs()
{
    sf::Vector3f* out = new sf::Vector3f(*posX, *posY, *posZ);
    return out;
}

sf::Vector3f* projection::AbstractObject::getRotationAbs()
{
    return &rotationAbs;
}

sf::Vector3f* projection::AbstractObject::getScaleAbs()
{
    return &scaleAbs;
}

void projection::AbstractObject::setName(std::string name)
{
    this->name_ = name;
}

void projection::AbstractObject::setPostion(sf::Vector3f position)
{
    *this->posX = position.x;
    *this->posY = position.y;
    *this->posZ = position.z;
}

void projection::AbstractObject::setRotation(sf::Vector3f rotation)
{
    this->rotationAbs = rotation;
}

void projection::AbstractObject::setScale(sf::Vector3f scale)
{
    this->scaleAbs = scale;
}
