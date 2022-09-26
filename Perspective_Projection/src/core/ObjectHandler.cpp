#include "ObjectHandler.h"

projection::ObjectHandler::ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target)
{
	this->pipeline = pipeLine;
	this->camera = camera;
	this->target = target;

	activeObj = nullptr;

	// Ressources
	ressources = new Ressources();
}

projection::ObjectHandler::~ObjectHandler()
{
	for (Texture* tex : textures) {
		delete tex;
	}
}

projection::Cube* projection::ObjectHandler::createCube(sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(cubes.size()));
	c->setGlobalOffset(camera->getOffset());
	cubes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

projection::Cube* projection::ObjectHandler::createCube(sf::Color color, sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(cubes.size()), color);
	c->setGlobalOffset(camera->getOffset());
	cubes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

projection::Cube* projection::ObjectHandler::createCube(Texture* texture, sf::Vector3f position, float size)
{
	//Cube* c = new Cube(position, size, target, "cube_" + std::to_string(cubes.size()), texture);
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(cubes.size()), textures[0]);
	c->setGlobalOffset(camera->getOffset());
	cubes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

projection::Point* projection::ObjectHandler::createPoint(sf::Vector3f position)
{
	Point* p = new Point(position, "point_" + std::to_string(points.size()));
	p->setGlobalOffset(camera->getOffset());
	points.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

projection::Triangle* projection::ObjectHandler::createPoly(sf::Color color, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(camera->getOffset());

	Triangle* t = new Triangle(p1, p2, p3, color, "polygon_" + std::to_string(polys.size()));

	t->deletePointsOnDestruction = true;
	t->setGlobalOffset(camera->getOffset());
	polys.push_back(t);
	pipeline->addObjectToQueue(t);

	return t;
}

projection::Triangle* projection::ObjectHandler::createPoly(Texture* texture, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(camera->getOffset());

	//Triangle* t = new Triangle(p1, p2, p3, texture, "polygon_" + std::to_string(polys.size()), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));
	Triangle* t = new Triangle(p1, p2, p3, textures[0], "polygon_" + std::to_string(polys.size()), sf::Vector2f(0.5f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));

	t->deletePointsOnDestruction = true;
	t->setGlobalOffset(camera->getOffset());
	polys.push_back(t);
	pipeline->addObjectToQueue(t);

	return t;
}

projection::Texture* projection::ObjectHandler::createTexture(TexType texture)
{
	Texture* tex = new Texture(ressources, "texture" + std::to_string(textures.size()));
	tex->setTexture(texture);
	this->textures.push_back(tex);
	return tex;
}

projection::Plane* projection::ObjectHandler::createPlane(sf::Vector3f position, sf::Vector2f scale, sf::Color color)
{
	Plane* p = new Plane(position, scale, target, "plane_" + std::to_string(cubes.size()), color);
	p->setGlobalOffset(camera->getOffset());
	planes.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

projection::Plane* projection::ObjectHandler::createPlane(Texture* texture, sf::Vector3f position, sf::Vector2f scale)
{
	Plane* p = new Plane(position, scale, target, "plane_" + std::to_string(cubes.size()), textures[0]);
	p->setGlobalOffset(camera->getOffset());
	planes.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

std::vector<projection::AbstractObject*>* projection::ObjectHandler::getObjects()
{
	std::vector<AbstractObject*> combList;
	combList.insert(combList.end(), cubes.begin(), cubes.end());
	combList.insert(combList.end(), points.begin(), points.end());
	combList.insert(combList.end(), polys.begin(), polys.end());
	return &combList;
}

std::vector<projection::Renderable*> projection::ObjectHandler::getRenderObjects()
{
	std::vector<Renderable*> combList;
	combList.insert(combList.end(), cubes.begin(), cubes.end());
	combList.insert(combList.end(), points.begin(), points.end());
	combList.insert(combList.end(), polys.begin(), polys.end());
	return combList;
}

std::vector<projection::Texture*>* projection::ObjectHandler::getTextures()
{
	return &textures;
}

projection::AbstractObject* projection::ObjectHandler::getActiveObj()
{
	// Remove in production
	//activeObj = cubes[0];
	// --
	return activeObj;
}

void projection::ObjectHandler::test_rotate(float dt)
{
	cubes[0]->rotateX(0.4f * dt);
	cubes[0]->rotateY(0.5f * dt);
	cubes[0]->rotateZ(0.6f * dt);
	//polys[0]->rotateZ(0.6f * dt, {0.f, 0.f, 0.f});
}
