#include "Texture.h"

void Texture::moveByValue(sf::Vector3f dir)
{
}

void Texture::moveToPos(sf::Vector3f pos)
{
}

std::vector<AbstractObject*> Texture::getChildren()
{
	return std::vector<AbstractObject*>();
}

Texture::Texture(Ressources* res, std::string name)
	:res(res)
{
	this->name_ = name;
	this->image = new sf::Image();
	dim = image->getSize();
}

Texture::~Texture()
{
	delete image;
}

void Texture::setTexture(TexType type)
{
	this->type = type;
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

sf::Sprite* Texture::getSpriteObject()
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromImage(*image);
	sf::Sprite* sprt = new sf::Sprite();
	sprt->setTexture(*tex);

	//delete tex;
	return sprt;
}

sf::Vector2u Texture::getSize()
{
	return dim;
}

TexType Texture::getType()
{
	return type;
}
