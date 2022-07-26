#include "Ressources.h"

Ressources::Ressources()
{
	textures[TexType::BRICKS] = new sf::Image();
	textures[TexType::BRICKS]->loadFromFile("Assets/texture/DROPPER.png");
}

sf::Image* Ressources::getTexture(TexType type)
{
	return textures[type];
}

sf::Vector2u Ressources::getDim(TexType type)
{
	return textures[type]->getSize();
}
