#pragma once

#include <vector>

#include "Renderable.h"
#include "Point.h"
#include "Mesh.h"

#include "MatrixOperations.h"

class Cube : public Mesh
{
public:
	Cube(sf::Vector3f position, float size, sf::Color color, sf::RenderTarget* target, bool wireFrame = true);
	~Cube();

	void connect(sf::RenderTarget* target) override;
};

