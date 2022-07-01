#pragma once

#include <vector>

#include "Renderable.h"
#include "Point.h"
#include "Mesh.h"

#include "MatrixOperations.h"

class Cube : public Mesh
{
private:
	std::vector<Point*> points;

	void createVert(int p1, int p2, sf::RenderTarget* target);
	bool wireFrame;

public:
	Cube(sf::Vector3f position, float size, sf::Color color, sf::RenderTarget* target, bool wireFrame = true);
	~Cube();

	void render(sf::RenderTarget* target) override;
	void applyPerspective(float distance) override;

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	void connect(sf::RenderTarget* target);

	std::vector<Point*>* getPoints();
};

