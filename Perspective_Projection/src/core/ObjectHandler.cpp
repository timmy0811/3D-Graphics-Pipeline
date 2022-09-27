#include "ObjectHandler.h"

projection::ObjectHandler::ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target)
{
	this->m_Pipeline = pipeLine;
	this->m_Camera = camera;
	this->m_Target = target;

	m_ActiveObject = nullptr;

	// Ressources
	m_Ressources = new Ressources();
}

projection::ObjectHandler::~ObjectHandler()
{
	for (Texture* tex : m_Textures) {
		delete tex;
	}
}

projection::Cube* projection::ObjectHandler::createCube(sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, m_Target, "cube_" + std::to_string(m_Cubes.size()));
	c->setGlobalOffset(m_Camera->getOffset());
	m_Cubes.push_back(c);
	m_Pipeline->addObjectToQueue(c);

	return c;
}

projection::Cube* projection::ObjectHandler::createCube(sf::Color color, sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, m_Target, "cube_" + std::to_string(m_Cubes.size()), color);
	c->setGlobalOffset(m_Camera->getOffset());
	m_Cubes.push_back(c);
	m_Pipeline->addObjectToQueue(c);

	return c;
}

projection::Cube* projection::ObjectHandler::createCube(Texture* texture, sf::Vector3f position, float size)
{
	//Cube* c = new Cube(position, size, target, "cube_" + std::to_string(cubes.size()), texture);
	Cube* c = new Cube(position, size, m_Target, "cube_" + std::to_string(m_Cubes.size()), m_Textures[0]);
	c->setGlobalOffset(m_Camera->getOffset());
	m_Cubes.push_back(c);
	m_Pipeline->addObjectToQueue(c);

	return c;
}

projection::Point* projection::ObjectHandler::createPoint(sf::Vector3f position)
{
	Point* p = new Point(position, "point_" + std::to_string(m_Points.size()));
	p->setGlobalOffset(m_Camera->getOffset());
	m_Points.push_back(p);
	m_Pipeline->addObjectToQueue(p);

	return p;
}

projection::Triangle* projection::ObjectHandler::createPoly(sf::Color color, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(m_Camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(m_Camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(m_Camera->getOffset());

	Triangle* t = new Triangle(p1, p2, p3, color, "polygon_" + std::to_string(m_Polys.size()));

	t->deletePointsOnDestruction = true;
	t->setGlobalOffset(m_Camera->getOffset());
	m_Polys.push_back(t);
	m_Pipeline->addObjectToQueue(t);

	return t;
}

projection::Triangle* projection::ObjectHandler::createPoly(Texture* texture, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(m_Camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(m_Camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(m_Camera->getOffset());

	//Triangle* t = new Triangle(p1, p2, p3, texture, "polygon_" + std::to_string(polys.size()), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));
	Triangle* t = new Triangle(p1, p2, p3, m_Textures[0], "polygon_" + std::to_string(m_Polys.size()), sf::Vector2f(0.5f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));

	t->deletePointsOnDestruction = true;
	t->setGlobalOffset(m_Camera->getOffset());
	m_Polys.push_back(t);
	m_Pipeline->addObjectToQueue(t);

	return t;
}

projection::Texture* projection::ObjectHandler::createTexture(TexType texture)
{
	Texture* tex = new Texture(m_Ressources, "texture" + std::to_string(m_Textures.size()));
	tex->setTexture(texture);
	this->m_Textures.push_back(tex);
	return tex;
}

projection::Plane* projection::ObjectHandler::createPlane(sf::Vector3f position, sf::Vector2f scale, sf::Color color)
{
	Plane* p = new Plane(position, scale, m_Target, "plane_" + std::to_string(m_Cubes.size()), color);
	p->setGlobalOffset(m_Camera->getOffset());
	m_Planes.push_back(p);
	m_Pipeline->addObjectToQueue(p);

	return p;
}

projection::Plane* projection::ObjectHandler::createPlane(Texture* texture, sf::Vector3f position, sf::Vector2f scale)
{
	Plane* p = new Plane(position, scale, m_Target, "plane_" + std::to_string(m_Cubes.size()), m_Textures[0]);
	p->setGlobalOffset(m_Camera->getOffset());
	m_Planes.push_back(p);
	m_Pipeline->addObjectToQueue(p);

	return p;
}

std::vector<projection::AbstractObject*>* projection::ObjectHandler::getObjects() const
{
	std::vector<AbstractObject*> combList;
	combList.insert(combList.end(), m_Cubes.begin(), m_Cubes.end());
	combList.insert(combList.end(), m_Points.begin(), m_Points.end());
	combList.insert(combList.end(), m_Polys.begin(), m_Polys.end());
	return &combList;
}

std::vector<projection::Renderable*> projection::ObjectHandler::getRenderObjects() const
{
	std::vector<Renderable*> combList;
	combList.insert(combList.end(), m_Cubes.begin(), m_Cubes.end());
	combList.insert(combList.end(), m_Points.begin(), m_Points.end());
	combList.insert(combList.end(), m_Polys.begin(), m_Polys.end());
	return combList;
}

std::vector<projection::Texture*>* projection::ObjectHandler::getTextures()
{
	return &m_Textures;
}

projection::AbstractObject* projection::ObjectHandler::getActiveObj() const
{
	// Remove in production
	//activeObj = cubes[0];
	// --
	return m_ActiveObject;
}

void projection::ObjectHandler::test_rotate(float dt)
{
	m_Cubes[0]->rotateX(0.4f * dt);
	m_Cubes[0]->rotateY(0.5f * dt);
	m_Cubes[0]->rotateZ(0.6f * dt);
	//polys[0]->rotateZ(0.6f * dt, {0.f, 0.f, 0.f});
}
