#pragma once

#include "Mesh.h"

class Cube : public Mesh
{
private:
	void init(sf::Vector3f position, float size);
public:
	Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name);
	Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, sf::Color color);
	Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, Texture* texture);

	~Cube();

	void connect(sf::RenderTarget* target) override;
};

