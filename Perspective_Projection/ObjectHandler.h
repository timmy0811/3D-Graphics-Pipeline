#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "Cube.h"
#include "Plane.h"
#include "Pipeline.h"

class ObjectHandler
{
private:
	// Rigids
	std::vector<Point*> points;
	std::vector<Triangle*> polys;
	std::vector<Mesh*> meshes;

	std::vector<AbstractObject*> tempObj;

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
	Cube* createCube(Texture* texture, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);

	Point* createPoint(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f));

	Triangle* createPoly(sf::Color color = sf::Color::Magenta, 
							sf::Vector3f position1 = sf::Vector3f(0.5f, 0.f, 0.f),
							sf::Vector3f position2 = sf::Vector3f(0.25f, -0.5f, 0.f),
							sf::Vector3f position3 = sf::Vector3f(0.f, 0.f, 0.f)); 
	Triangle* createPoly(Texture* texture, sf::Vector3f position1 = sf::Vector3f(0.5f, 0.f, 0.f),
						sf::Vector3f position2 = sf::Vector3f(0.25f, -0.5f, 0.f),
						sf::Vector3f position3 = sf::Vector3f(0.f, 0.f, 0.f));

	Texture* createTexture(TexType texture);

	Plane* createPlane(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), sf::Vector2f scale = sf::Vector2f(1.f, 1.f), sf::Color color = sf::Color::White);
	Plane* createPlane(Texture* texture, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), sf::Vector2f scale = sf::Vector2f(1.f, 1.f));

	std::vector<AbstractObject*>* getObjects();
	std::vector<Texture*>* getTextures();
	AbstractObject* getActiveObj();

	void clipTriangles(sf::Vector3f* globalOffset_);
	void clearClippingBuffer();

	void test_rotate(float dt);
};

