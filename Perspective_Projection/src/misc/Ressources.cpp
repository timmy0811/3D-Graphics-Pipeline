#include "Ressources.h"

projection::Ressources::Ressources()
{
	textures[TexType::BRICKS] = new sf::Image();
	textures[TexType::BRICKS]->loadFromFile("Assets/texture/BRICKS.png");

	textures[TexType::DIAMOND] = new sf::Image();
	textures[TexType::DIAMOND]->loadFromFile("Assets/texture/DIAMOND.png");

	textures[TexType::DROPPER] = new sf::Image();
	textures[TexType::DROPPER]->loadFromFile("Assets/texture/DROPPER.png");

	textures[TexType::ANDESIT] = new sf::Image();
	textures[TexType::ANDESIT]->loadFromFile("Assets/texture/ANDESIT.png");
}

sf::Image* projection::Ressources::getTexture(TexType type) 
{
	return textures[type];
}

sf::Vector2u projection::Ressources::getDim(TexType type) 
{
	return textures[type]->getSize();
}
