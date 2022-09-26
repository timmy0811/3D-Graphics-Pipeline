#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

namespace projection {
	class AbstractObject
	{
	protected:
		std::string name_;

		float* posX;
		float* posY;
		float* posZ;

		sf::Vector3f rotationAbs;
		sf::Vector3f scaleAbs;

	public:
		std::string getName();

		sf::Vector3f* getPositionAbs();
		sf::Vector3f* getRotationAbs();
		sf::Vector3f* getScaleAbs();

		void setName(std::string name);
		void setPostion(sf::Vector3f position);
		void setRotation(sf::Vector3f rotation);
		void setScale(sf::Vector3f scale);

		virtual void moveByValue(sf::Vector3f dir) = 0;
		virtual void moveToPos(sf::Vector3f pos) = 0;

		virtual std::vector<AbstractObject*> getChildren() = 0;
	};
}


