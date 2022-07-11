#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

class AbstractObject
{
protected:
	std::string name_;
	sf::Vector3f position;
	sf::Vector3f rotation;
	sf::Vector3f scale;

public:
	std::string getName();

	sf::Vector3f* getPosition();
	sf::Vector3f* getRotation();
	sf::Vector3f* getScale();

	virtual std::vector<AbstractObject*> getChildren() = 0;
};

