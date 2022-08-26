#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "Mesh.h"

class WavefrontObj : public Mesh
{
private:
	std::string material;
	std::vector<sf::Vector2f> vt;

public:
	WavefrontObj() = default;
	~WavefrontObj();

	const bool loadFromFile(char* path, Texture* texture = nullptr);
	void connect(sf::RenderTarget* target) override;
};