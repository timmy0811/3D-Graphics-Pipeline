#include "AbstractObject.h"

std::string AbstractObject::getName()
{
    return name_;
}

sf::Vector3f* AbstractObject::getPositionAbs()
{
    sf::Vector3f* out = new sf::Vector3f(*posX, *posY, *posZ);
    return out;
}

sf::Vector3f* AbstractObject::getRotationAbs()
{
    return &rotationAbs;
}

sf::Vector3f* AbstractObject::getScaleAbs()
{
    return &scaleAbs;
}

void AbstractObject::setName(std::string name)
{
    this->name_ = name;
}

void AbstractObject::setPostion(sf::Vector3f position)
{
    *this->posX = position.x;
    *this->posY = position.y;
    *this->posZ = position.z;
}

void AbstractObject::setRotation(sf::Vector3f rotation)
{
    this->rotationAbs = rotation;
}

void AbstractObject::setScale(sf::Vector3f scale)
{
    this->scaleAbs = scale;
}
