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
	:m_Ressources(res)
{
	this->name_ = name;
	this->m_Image = new sf::Image();
	m_Dimensions = m_Image->getSize();
}

projection::Texture::~Texture()
{
	delete m_Image;
}

void projection::Texture::setTexture(TexType type)
{
	this->m_TexType = type;
	delete m_Image;
	m_Image = m_Ressources->getTexture(type);
	m_Dimensions = m_Image->getSize();
}

const sf::Uint8* projection::Texture::getPixelPtr(unsigned int x, unsigned int y) const
{
	if (x >= m_Dimensions.x) x = m_Dimensions.x - 1;
	if (y >= m_Dimensions.y) y = m_Dimensions.y - 1;

	return m_Image->getPixelsPtr() + (y * m_Dimensions.x + x) * 4;
}

const sf::Uint8* projection::Texture::getPixelPtr() const
{
	return m_Image->getPixelsPtr();
}

sf::Sprite* projection::Texture::getSpriteObject() const
{
	sf::Texture* tex = new sf::Texture();
	tex->loadFromImage(*m_Image);
	sf::Sprite* sprt = new sf::Sprite();
	sprt->setTexture(*tex);

	//delete tex;
	return sprt;
}

sf::Vector2u projection::Texture::getSize() const
{
	return m_Dimensions;
}

projection::TexType projection::Texture::getType() const
{
	return m_TexType;
}
