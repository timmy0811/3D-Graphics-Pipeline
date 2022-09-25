#pragma once

#include <SFML/Graphics.hpp>

#include "Ressources.h"
#include "AbstractObject.h"

class Texture : public AbstractObject
{
private:
	sf::Image* image;
	sf::Vector2u dim;

	Ressources* res;

	TexType type;

	void moveByValue(sf::Vector3f dir) override;
	void moveToPos(sf::Vector3f pos) override;

	std::vector<AbstractObject*> getChildren() override;

public:
	Texture(Ressources* res, std::string name = "Texture");
	~Texture();

	void setTexture(TexType type);
	
	const sf::Uint8* getPixelPtr(unsigned int x, unsigned int y);
	const sf::Uint8* getPixelPtr();

	sf::Sprite* getSpriteObject();

	sf::Vector2u getSize();
	TexType getType();
};