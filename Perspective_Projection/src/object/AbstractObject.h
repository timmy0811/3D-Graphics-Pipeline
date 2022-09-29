#pragma once

#include <vector>
#include <string>

#include <SFML/Graphics.hpp>

namespace projection {
	class AbstractObject
	{
	protected:
		std::string name_;

		float* m_PosX;
		float* m_PosY;
		float* m_PosZ;

		sf::Vector3f m_RotationAbsolute;
		sf::Vector3f m_ScaleAbsolute;

	public:
		std::string getName() const;

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


