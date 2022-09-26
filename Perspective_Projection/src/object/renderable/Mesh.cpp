#include "Mesh.h"

void projection::Mesh::createVert(int p1, int p2, sf::RenderTarget* target)
{
	if (points[p1]->getPosition().z + globalOffset_->z > c_z_clipping || points[p2]->getPosition().z + globalOffset_->z > c_z_clipping) return;
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = translateToRel(sf::Vector2f(points[p1]->getProjMatrix()->x0, points[p1]->getProjMatrix()->y0), target->getSize());
	line[1].position = translateToRel(sf::Vector2f(points[p2]->getProjMatrix()->x0, points[p2]->getProjMatrix()->y0), target->getSize());

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	vertices.push_back(line);
}

void projection::Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle* poly = new Triangle(p1, p2, p3, color, "Triangle");
	poly->setGlobalOffset(globalOffset_);
	polys.push_back(poly);
}

void projection::Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_)
{
	Triangle* poly = new Triangle(p1, p2, p3, texture, "Triangle", texCord1_, texCord2_, texCord3_);
	poly->setGlobalOffset(globalOffset_);
	polys.push_back(poly);
}

projection::Mesh::~Mesh()
{
	for (Triangle* poly : polys) {
		delete poly;
	}

	for (Point* point : points) {
		delete point;
	}
}

void projection::Mesh::rotateX(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateX(angle, pos);
	}
}

void projection::Mesh::rotateY(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateY(angle, pos);
	}
}

void projection::Mesh::rotateZ(float angle)
{
	sf::Vector3f pos = maop::matToVec(&meshCenter);
	for (Point* point : points) {
		point->rotateZ(angle, pos);
	}
}

void projection::Mesh::rotateX(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : polys) {
		poly->rotateX(angle, refPosition);
	}
}

void projection::Mesh::rotateY(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : polys) {
		poly->rotateY(angle, refPosition);
	}
}

void projection::Mesh::rotateZ(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : polys) {
		poly->rotateZ(angle, refPosition);
	}
}

void projection::Mesh::rotateByCamera(float angle, sf::Vector3f refPosition)
{
	for (Point* p : points) {
		p->rotateY(angle, refPosition);
	}
}

void projection::Mesh::moveByValue(sf::Vector3f dir)
{
	for (Point* point : points) {
		point->moveByValue(dir);
	}
}

void projection::Mesh::moveToPos(sf::Vector3f pos)
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

void projection::Mesh::setGlobalOffset(sf::Vector3f* vec)
{
	for (Point* point : points) {
		point->setGlobalOffset(vec);
	}
	for (Triangle* poly : polys) {
		poly->setGlobalOffset(vec);
	}
	this->globalOffset_ = vec;
}

void projection::Mesh::applyPerspective()
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

void projection::Mesh::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	for (Point* p : points) {
		p->render(target);
	}

	for (int i = 0; i < vertices.size(); i++) {
		/*if(p1->getPosition().z + globalOffset_->z > c_z_clipping)*/
		target->draw(vertices[i]);
	}

	sortPolys();

	for (Triangle* poly : polys) {
		poly->render(target, buffer);
	}
}

std::vector<projection::AbstractObject*> projection::Mesh::getChildren()
{
	std::vector<AbstractObject*> outVec;
	for (Point* p : points) {
		outVec.push_back(p);
	}
	return outVec;
}

std::vector<projection::Point*>* projection::Mesh::getPoints()
{
	return &points;
}

void projection::Mesh::sortPolys()
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
