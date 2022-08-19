#include "ObjectHandler.h"

ObjectHandler::ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target)
{
	this->pipeline = pipeLine;
	this->camera = camera;
	this->target = target;

	activeObj = nullptr;

	// Ressources
	ressources = new Ressources();
}

ObjectHandler::~ObjectHandler()
{
	for (Texture* tex : textures) {
		delete tex;
	}
}

Cube* ObjectHandler::createCube(sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(meshes.size()));
	c->setGlobalOffset(camera->getOffset());
	meshes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

Cube* ObjectHandler::createCube(sf::Color color, sf::Vector3f position, float size)
{
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(meshes.size()), color);
	c->setGlobalOffset(camera->getOffset());
	meshes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
}

Cube* ObjectHandler::createCube(Texture* texture, sf::Vector3f position, float size)
{
	//Cube* c = new Cube(position, size, target, "cube_" + std::to_string(meshes.size()), texture);
	Cube* c = new Cube(position, size, target, "cube_" + std::to_string(meshes.size()), textures[0]);
	c->setGlobalOffset(camera->getOffset());
	meshes.push_back(c);
	pipeline->addObjectToQueue(c);

	return c;
	activeObj = c;
}

Point* ObjectHandler::createPoint(sf::Vector3f position)
{
	Point* p = new Point(position, "point_" + std::to_string(points.size()));
	p->setGlobalOffset(camera->getOffset());
	points.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

Triangle* ObjectHandler::createPoly(sf::Color color, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
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

Triangle* ObjectHandler::createPoly(Texture* texture, sf::Vector3f position1, sf::Vector3f position2, sf::Vector3f position3)
{
	Point* p1 = new Point(position1, "point_0");
	p1->setGlobalOffset(camera->getOffset());

	Point* p2 = new Point(position2, "point_1");
	p2->setGlobalOffset(camera->getOffset());

	Point* p3 = new Point(position3, "point_2");
	p3->setGlobalOffset(camera->getOffset());

	//Triangle* t = new Triangle(p1, p2, p3, texture, "polygon_" + std::to_string(polys.size()), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));
	Triangle* t = new Triangle(p1, p2, p3, textures[0], "polygon_" + std::to_string(polys.size()), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));

	t->deletePointsOnDestruction = true;
	t->setGlobalOffset(camera->getOffset());
	polys.push_back(t);
	pipeline->addObjectToQueue(t);

	return t;
}


Texture* ObjectHandler::createTexture(TexType texture)
{
	Texture* tex = new Texture(ressources, "texture" + std::to_string(textures.size()));
	tex->setTexture(texture);
	this->textures.push_back(tex);
	return tex;
}

Plane* ObjectHandler::createPlane(sf::Vector3f position, sf::Vector2f scale, sf::Color color)
{
	Plane* p = new Plane(position, scale, target, "plane_" + std::to_string(meshes.size()), color);
	p->setGlobalOffset(camera->getOffset());
	meshes.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

Plane* ObjectHandler::createPlane(Texture* texture, sf::Vector3f position, sf::Vector2f scale)
{
	Plane* p = new Plane(position, scale, target, "plane_" + std::to_string(meshes.size()), textures[1]);
	p->setGlobalOffset(camera->getOffset());
	meshes.push_back(p);
	pipeline->addObjectToQueue(p);

	return p;
}

std::vector<AbstractObject*>* ObjectHandler::getObjects()
{
	std::vector<AbstractObject*> combList;
	combList.insert(combList.end(), meshes.begin(), meshes.end());
	combList.insert(combList.end(), points.begin(), points.end());
	combList.insert(combList.end(), polys.begin(), polys.end());
	return &combList;
}

std::vector<Texture*>* ObjectHandler::getTextures()
{
	return &textures;
}

AbstractObject* ObjectHandler::getActiveObj()
{
	// Remove in production
	//activeObj = meshes[0];
	// --
	return activeObj;
}

void ObjectHandler::test_rotate(float dt)
{
	/*meshes[0]->rotateX(0.4f * dt);
	meshes[0]->rotateY(0.5f * dt);*/
	meshes[0]->rotateZ(0.01f * dt);
}

void ObjectHandler::clipTriangles(sf::Vector3f* globalOffset_)
{
	std::vector<Triangle*> tris = this->polys;
	for (Mesh* mesh : meshes) {
		tris.insert(tris.end(), mesh->getPolys()->begin(), mesh->getPolys()->end());
	}

	std::vector<Point*> outsidePoints{};
	std::vector<Point*> insidePoints{};

	std::vector<int> outsideIndex;
	std::vector<int> insideIndex;

	sf::Vector2f outPos;
	sf::Vector2f inPos;

	for (Triangle* triangle : tris) {
		outsidePoints.clear();
		insidePoints.clear();

		outsideIndex.clear();
		insideIndex.clear();

		std::vector<Point*> points = triangle->getPoints();
		for (int i = 0; i < points.size(); i++) {
			if (points[i]->getScreenPosition(target).x < 0.f) {
				outsidePoints.push_back(points[i]);		// translated Position
				outsideIndex.push_back(i);
			}
			else {
				insidePoints.push_back(points[i]);
				insideIndex.push_back(i);
			}
		}

		if (outsidePoints.size() == 0) triangle->clipped = false;
		if (outsidePoints.size() == 1) {
			outPos = outsidePoints[0]->getScreenPosition(target);
			inPos = insidePoints[0]->getScreenPosition(target);
			float outW = outsidePoints[0]->getW();
			float inW = insidePoints[0]->getW();

			std::vector<sf::Vector2f> texCords;
			texCords.push_back(triangle->getTexCord(1));
			texCords.push_back(triangle->getTexCord(2));
			texCords.push_back(triangle->getTexCord(3));

			sf::Vector2f* texCord1 = new sf::Vector2f();
			sf::Vector3f* pos = new sf::Vector3f();

			pos->x = 0.f;
			pos->y = outPos.y + (0 - outPos.x) * (inPos.y - outPos.y) / (inPos.x - outPos.x);
			//pos->z = outPos.z + (0 - outPos.x) * (inPos.z - outPos.z) / (inPos.x - outPos.x);
			pos->z = 0.f;

			texCord1->x = texCords[outsideIndex[0]].x + (0 - outPos.x) * (texCords[insideIndex[0]].x - texCords[outsideIndex[0]].x) / (inPos.y - outPos.x);
			texCord1->y = texCords[outsideIndex[0]].y + (0 - outPos.x) * (texCords[insideIndex[0]].y - texCords[outsideIndex[0]].y) / (inPos.x - outPos.x);
			float w = outW + (0 - outPos.x) * (inW - outW) / (inPos.x - outPos.x);

			Point edgePoint1 = Point(*pos, "point_" + std::to_string(outsideIndex[0]), nullptr, true);

			inPos = insidePoints[1]->getScreenPosition(target);
			sf::Vector2f* texCord2 = new sf::Vector2f();

			pos->x = 0.f;
			pos->y = outPos.y + (0 - outPos.x) * (inPos.y - outPos.y) / (inPos.x - outPos.x);
			//pos->z = outPos.z + (0 - outPos.x) * (inPos.z - outPos.z) / (inPos.x - outPos.x);
			pos->z = 0.f;

			texCord2->x = texCords[outsideIndex[0]].x + (0 - outPos.x) * (texCords[insideIndex[1]].x - texCords[outsideIndex[0]].x) / (inPos.y - outPos.x);
			texCord2->y = texCords[outsideIndex[0]].y + (0 - outPos.x) * (texCords[insideIndex[1]].y - texCords[outsideIndex[0]].y) / (inPos.x - outPos.x);
			float w2 = outW + (0 - outPos.x) * (inW - outW) / (inPos.x - outPos.x);

			Point edgePoint2 = Point(*pos, "point_" + std::to_string(outsideIndex[0]), nullptr, true);

			if (triangle->isTextured) {
				Triangle* out0 = new Triangle(edgePoint1.getPosition(), (insidePoints)[0]->convertToScreenCoordinates(target), (insidePoints)[1]->convertToScreenCoordinates(target), triangle->getTexture(), "triangle", *texCord1, texCords[insideIndex[0]], texCords[insideIndex[1]]);
				Triangle* out1 = new Triangle(edgePoint2.getPosition(), edgePoint1.getPosition(), (insidePoints)[1]->convertToScreenCoordinates(target), triangle->getTexture(), "triangle", *texCord2, *texCord1, texCords[insideIndex[1]]);

				tempObj.push_back(out0);
				tempObj.push_back(out1);

				pipeline->addTempObjectToQueue(out0);
				pipeline->addTempObjectToQueue(out1);

				triangle->clipped = true;
			}
			else {
				Triangle* out0 = new Triangle(edgePoint1.getPosition(), (insidePoints)[0]->convertToScreenCoordinates(target), (insidePoints)[1]->convertToScreenCoordinates(target), sf::Color::Blue, "triangle", true);
				Triangle* out1 = new Triangle(edgePoint2.getPosition(), edgePoint1.getPosition(), (insidePoints)[1]->convertToScreenCoordinates(target), sf::Color::Red, "triangle", true);

				tempObj.push_back(out0);
				tempObj.push_back(out1);

				pipeline->addTempObjectToQueue(out0);
				pipeline->addTempObjectToQueue(out1);

				triangle->clipped = true;
			}
			//delete triangle;
		}
	}
}

void ObjectHandler::clearClippingBuffer()
{
	for (AbstractObject* obj : tempObj) {
		delete obj;
	}

	tempObj.clear();
}
