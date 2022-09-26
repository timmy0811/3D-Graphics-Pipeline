#include "Texture.h"

void projection::Texture::moveByValue(sf::Vector3f dir)
{
}

void projection::Texture::moveToPos(sf::Vector3f pos)
{
}

std::vector<projection::AbstractObject*> projection::Texture::getChildren()
{
	return std::vector<AbstractObject*>();
}

projection::Texture::Texture(Ressources* res, std::string name)
	:res(res)
{
	this->name_ = name;
	this->image = new sf::Image();
	dim = image->getSize();
}

projection::Texture::~Texture()
{
	delete image;
}

void projection::Texture::setTexture(TexType type)
{
	this->type = type;
	delete image;
	image = res->getTexture(type);
	dim = image->getSize();
}

const sf::Uint8* projection::Texture::getPixelPtr(unsigned int x, unsigned int y)
{
	if (x >= dim.x) x = dim.x - 1;
	if (y >= dim.y) y = dim.y - 1;

	return image->getPixelsPtr() + (y * dim.x + x) * 4;
}

const sf::Uint8* projection::Texture::getPixelPtr()
{
	return image->getPixelsPtr();
}

sf::Sprite* projection::Texture::getSpriteObject()
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromImage(*image);
	sf::Sprite* sprt = new sf::Sprite();
	sprt->setTexture(*tex);

	//delete tex;
	return sprt;
}

sf::Vector2u projection::Texture::getSize()
{
	return dim;
}

projection::TexType projection::Texture::getType()
{
	return type;
}
