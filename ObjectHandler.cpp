#include "ObjectHandler.h"

ObjectHandler::ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target)
{
	this->pipeline = pipeLine;
	this->camera = camera;
	this->target = target;

	activeObj = nullptr;
}

Cube* ObjectHandler::createCube(sf::Vector3f position, float size, sf::Color color)
{
	Cube* c = new Cube(position, size, color, target, "cube_" + std::to_string(cubes.size()));
	c->setGlobalOffset(camera->getOffset());
	cubes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

Point* ObjectHandler::createPoint(sf::Vector3f position)
{
	Point* p = new Point(position, "point_" + std::to_string(points.size()));
	p->setGlobalOffset(camera->getOffset());
	points.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

Triangle* ObjectHandler::createPoly(sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3, sf::Color color)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(camera->getOffset());

	Triangle* t = new Triangle(p1, p2, p3, color, "polygon_" + std::to_string(polys.size()));
	t->setGlobalOffset(camera->getOffset());
	polys.push_back(t);
	pipeline->addObjectToQueue(t);

	return t;
}

std::vector<AbstractObject*> ObjectHandler::getObjects()
{
	std::vector<AbstractObject*> combList;
	combList.insert(combList.end(), cubes.begin(), cubes.end());
	combList.insert(combList.end(), points.begin(), points.end());
	combList.insert(combList.end(), polys.begin(), polys.end());
	return combList;
}

AbstractObject* ObjectHandler::getActiveObj()
{
	// Remove in production
	activeObj = cubes[0];
	// --
	return activeObj;
}
