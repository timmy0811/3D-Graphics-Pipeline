#include "Texture.h"

Texture::Texture(Ressources* res)
	:res(res)
{
	this->image = new sf::Image();
	dim = image->getSize();
}

Texture::~Texture()
{
	delete image;
}

void Texture::setTexture(TexType type)
{
	delete image;
	image = res->getTexture(type);
	dim = image->getSize();
}

const sf::Uint8* Texture::getPixelPtr(unsigned int x, unsigned int y)
{
	if (x >= dim.x) x = dim.x - 1;
	if (y >= dim.y) y = dim.y - 1;

	return image->getPixelsPtr() + (y * dim.x + x) * 4;
}

const sf::Uint8* Texture::getPixelPtr()
{
	return image->getPixelsPtr();
}

sf::Vector2u Texture::getSize()
{
	return dim;
}
