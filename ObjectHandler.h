#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "Cube.h"
#include "Pipeline.h"

class ObjectHandler
{
private:
	std::vector<Cube*> cubes;
	std::vector<Point*> points;
	std::vector<Triangle*> polys;

	Pipeline* pipeline;
	Camera* camera;
	sf::RenderTarget* target;

	AbstractObject* activeObj;

public:
	ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target);

	Cube* createCube(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f, sf::Color color = sf::Color::White);
	Point* createPoint(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f));
	Triangle* createPoly(sf::Vector3f position1 = sf::Vector3f(0.5f, 0.f, 0.f),
							sf::Vector3f position2 = sf::Vector3f(0.25f, -0.5f, 0.f),
							sf::Vector3f position3 = sf::Vector3f(0.f, 0.f, 0.f),
							sf::Color color = sf::Color::Magenta); 

	std::vector<AbstractObject*> getObjects();
	AbstractObject* getActiveObj();
};

