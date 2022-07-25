#include "Mesh.h"

void Mesh::createVert(int p1, int p2, sf::RenderTarget* target)
{
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = translateToRel(sf::Vector2f(points[p1]->getProjMatrix()->x0, points[p1]->getProjMatrix()->y0), target->getSize());
	line[1].position = translateToRel(sf::Vector2f(points[p2]->getProjMatrix()->x0, points[p2]->getProjMatrix()->y0), target->getSize());

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	vertices.push_back(line);
}

void Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle* poly = new Triangle(p1, p2, p3, color, "Triangle");
	poly->setGlobalOffset(globalOffset_);
	polys.push_back(poly);
}

void Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_)
{
	Triangle* poly = new Triangle(p1, p2, p3, texture, "Triangle", texCord1_, texCord2_, texCord3_);
	poly->setGlobalOffset(globalOffset_);
	polys.push_back(poly);
}

Mesh::~Mesh()
{
	for (Triangle* poly : polys) {
		delete poly;
	}

	for (Point* point : points) {
		delete point;
	}
}

void Mesh::rotateX(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateX(angle, pos);
	}
}

void Mesh::rotateY(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateY(angle, pos);
	}
}

void Mesh::rotateZ(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateZ(angle, pos);
	}
}

void Mesh::rotateX(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::rotateY(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::rotateZ(float angle, sf::Vector3f refPosition)
{
	return;
}

void Mesh::moveByValue(sf::Vector3f dir)
{
	for (Point* point : points) {
		point->moveByValue(dir);
	}
}

void Mesh::moveToPos(sf::Vector3f pos)
{
	for (Point* point : points) {
		sf::Vector3f* posRelToCube = new sf::Vector3f;
		posRelToCube->x = point->getPosition().x - *posX + pos.x;
		posRelToCube->y = point->getPosition().y - *posY + pos.y;
		posRelToCube->z = point->getPosition().z - *posZ + pos.z;

		point->moveToPos(*posRelToCube);
		delete posRelToCube;
	}

	sf::Vector3f* posRelToCube = new sf::Vector3f;
	meshCenter.x0 = meshCenter.x0 - *posX + pos.x;
	meshCenter.y0 = meshCenter.y0 - *posY + pos.y;
	meshCenter.z0 = meshCenter.z0 - *posZ + pos.z;

	delete posRelToCube;

	*posX = pos.x;
	*posY = pos.y;
	*posZ = pos.z;
}

void Mesh::setGlobalOffset(sf::Vector3f* vec)
{
	for (Point* point : points) {
		point->setGlobalOffset(vec);
	}
	for (Triangle* poly : polys) {
		poly->setGlobalOffset(vec);
	}
}

void Mesh::applyPerspective()
{
	for (Point* p : points) {
		p->applyPerspective();
	}

	connect(target);

	if (!wireFrame_) {
		for (Triangle* poly : polys) {
			poly->applyPerspective();
		}
	}
}

void Mesh::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	for (Point* p : points) {
		//p->render(target);
	}

	for (int i = 0; i < vertices.size(); i++) {
		target->draw(vertices[i]);
	}

	sortPolys();

	for (Triangle* poly : polys) {
		poly->render(target, buffer);
	}
}

std::vector<AbstractObject*> Mesh::getChildren()
{
	std::vector<AbstractObject*> outVec;
	for (Point* p : points) {
		outVec.push_back(p);
	}
	return outVec;
}

std::vector<Point*>* Mesh::getPoints()
{
	return &points;
}

void Mesh::sortPolys()
{
	unsigned int swaps = 1;
	while (swaps > 0) {
		swaps = 0;
		for (int i = 0; i < polys.size(); i++) {
			if (i + 1.f >= polys.size()) continue;
			if (polys[static_cast<std::vector<Triangle*, std::allocator<Triangle*>>::size_type>(i) + 1]->averageZ() < polys[i]->averageZ()) {
				Triangle* tempPoly = polys[i];
				polys[i] = polys[(int) (i + 1.f)];
				polys[(int) (i + 1.f)] = tempPoly;
				swaps++;
			}
		}
	}
}
