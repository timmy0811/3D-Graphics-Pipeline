#pragma once

#include <SFML/Graphics.hpp>

#include "../misc/Ressources.h"
#include "AbstractObject.h"

namespace projection {
	class Texture : public AbstractObject
	{
	private:
		sf::Image* m_Image;
		sf::Vector2u m_Dimensions;

		Ressources* m_Ressources;

		TexType m_TexType;

		void moveByValue(sf::Vector3f dir) override;
		void moveToPos(sf::Vector3f pos) override;

		std::vector<AbstractObject*> getChildren() override;

	public:
		Texture(Ressources* res, std::string name = "Texture");
		~Texture();

		void setTexture(TexType type);
	
		const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y) const;
		const sf::Uint8* getPixelPtr() const;

		sf::Sprite* getSpriteObject() const;

		sf::Vector2u getSize() const;
		TexType getType() const;
	};
}
