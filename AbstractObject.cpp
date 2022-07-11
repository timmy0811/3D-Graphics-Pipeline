#include "AbstractObject.h"

std::string AbstractObject::getName()
{
    return name_;
}

sf::Vector3f* AbstractObject::getPosition()
{
    return &position;
}

sf::Vector3f* AbstractObject::getRotation()
{
    return &rotation;
}

sf::Vector3f* AbstractObject::getScale()
{
    return &scale;
}
