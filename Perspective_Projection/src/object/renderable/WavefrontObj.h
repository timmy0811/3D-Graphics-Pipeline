#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "Mesh.h"

class WavefrontObj : public Mesh
{
private:
	std::string material;

public:
	WavefrontObj() = default;
	~WavefrontObj();

	const bool loadFromFile(char* path);
	void connect(sf::RenderTarget* target) override;
};