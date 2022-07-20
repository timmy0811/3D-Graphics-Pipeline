#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "Cube.h"
#include "Pipeline.h"

class ObjectHandler
{
private:
	// Rigids
	std::vector<Cube*> cubes;
	std::vector<Point*> points;
	std::vector<Triangle*> polys;

	// Textures
	std::vector<Texture*> textures;

	Pipeline* pipeline;
	Camera* camera;
	sf::RenderTarget* target;

	AbstractObject* activeObj;

	// Ressources;
	Ressources* ressources;

public:
	ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target);
	~ObjectHandler();

	Cube* createCube(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);
	Cube* createCube(sf::Color color, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);
	Cube* createCube(Texture* texture = nullptr, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);

	Point* createPoint(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f));
	Triangle* createPoly(sf::Vector3f position1 = sf::Vector3f(0.5f, 0.f, 0.f),
							sf::Vector3f position2 = sf::Vector3f(0.25f, -0.5f, 0.f),
							sf::Vector3f position3 = sf::Vector3f(0.f, 0.f, 0.f),
							sf::Color color = sf::Color::Magenta); 

	Texture* createTexture(TexType texture);

	std::vector<AbstractObject*> getObjects();
	AbstractObject* getActiveObj();

	void test_rotate(float dt);
};

