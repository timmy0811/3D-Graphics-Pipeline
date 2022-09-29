#include "Mesh.h"

void projection::Mesh::createVert(int p1, int p2, sf::RenderTarget* target)
{
	if (m_Points[p1]->getPosition().z + m_GlobalOffset->z > c_z_clipping || m_Points[p2]->getPosition().z + m_GlobalOffset->z > c_z_clipping) return;
	sf::VertexArray line(sf::Lines, 2);
	line[0].position = translateToRel(sf::Vector2f(m_Points[p1]->getProjMatrix()->x0, m_Points[p1]->getProjMatrix()->y0), target->getSize());
	line[1].position = translateToRel(sf::Vector2f(m_Points[p2]->getProjMatrix()->x0, m_Points[p2]->getProjMatrix()->y0), target->getSize());

	line[0].color = sf::Color::White;
	line[1].color = sf::Color::White;

	m_Vertices.push_back(line);
}

void projection::Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color)
{
	Triangle* poly = new Triangle(p1, p2, p3, color, "Triangle");
	poly->setGlobalOffset(m_GlobalOffset);
	m_Polys.push_back(poly);
}

void projection::Mesh::createTriangle(Point* p1, Point* p2, Point* p3, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_)
{
	Triangle* poly = new Triangle(p1, p2, p3, m_Texture, "Triangle", texCord1_, texCord2_, texCord3_);
	poly->setGlobalOffset(m_GlobalOffset);
	m_Polys.push_back(poly);
}

projection::Mesh::~Mesh()
{
	for (Triangle* poly : m_Polys) {
		delete poly;
	}

	for (Point* point : m_Points) {
		delete point;
	}
}

void projection::Mesh::rotateX(float angle)
{
	sf::Vector3f pos = maop::matToVec(&m_MeshCenter);
	for (Point* point : m_Points) {
		point->rotateX(angle, pos);
	}
}

void projection::Mesh::rotateY(float angle)
{
	sf::Vector3f pos = maop::matToVec(&m_MeshCenter);
	for (Point* point : m_Points) {
		point->rotateY(angle, pos);
	}
}

void projection::Mesh::rotateZ(float angle)
{
	sf::Vector3f pos = maop::matToVec(&m_MeshCenter);
	for (Point* point : m_Points) {
		point->rotateZ(angle, pos);
	}
}

void projection::Mesh::rotateX(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : m_Polys) {
		poly->rotateX(angle, refPosition);
	}
}

void projection::Mesh::rotateY(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : m_Polys) {
		poly->rotateY(angle, refPosition);
	}
}

void projection::Mesh::rotateZ(float angle, sf::Vector3f refPosition)
{
	for (Triangle* poly : m_Polys) {
		poly->rotateZ(angle, refPosition);
	}
}

void projection::Mesh::rotateByCamera(float angle, sf::Vector3f refPosition)
{
	for (Point* p : m_Points) {
		p->rotateY(angle, refPosition);
	}
}

void projection::Mesh::moveByValue(sf::Vector3f dir)
{
	for (Point* point : m_Points) {
		point->moveByValue(dir);
	}
}

void projection::Mesh::moveToPos(sf::Vector3f pos)
{
	for (Point* point : m_Points) {
		sf::Vector3f* posRelToCube = new sf::Vector3f;
		posRelToCube->x = point->getPosition().x - *m_PosX + pos.x;
		posRelToCube->y = point->getPosition().y - *m_PosY + pos.y;
		posRelToCube->z = point->getPosition().z - *m_PosZ + pos.z;

		point->moveToPos(*posRelToCube);
		delete posRelToCube;
	}

	sf::Vector3f* posRelToCube = new sf::Vector3f;
	m_MeshCenter.x0 = m_MeshCenter.x0 - *m_PosX + pos.x;
	m_MeshCenter.y0 = m_MeshCenter.y0 - *m_PosY + pos.y;
	m_MeshCenter.z0 = m_MeshCenter.z0 - *m_PosZ + pos.z;

	delete posRelToCube;

	*m_PosX = pos.x;
	*m_PosY = pos.y;
	*m_PosZ = pos.z;
}

void projection::Mesh::setGlobalOffset(sf::Vector3f* vec)
{
	for (Point* point : m_Points) {
		point->setGlobalOffset(vec);
	}
	for (Triangle* poly : m_Polys) {
		poly->setGlobalOffset(vec);
	}
	this->m_GlobalOffset = vec;
}

void projection::Mesh::applyPerspective()
{
	for (Point* p : m_Points) {
		p->applyPerspective();
	}

	connect(m_Target);

	if (!wireFrame_) {
		for (Triangle* poly : m_Polys) {
			poly->applyPerspective();
		}
	}
}

void projection::Mesh::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	for (Point* p : m_Points) {
		if(c_drawMeshPoints) p->render(target);
	}

	for (int i = 0; i < m_Vertices.size(); i++) {
		/*if(p1->getPosition().z + globalOffset_->z > c_z_clipping)*/
		target->draw(m_Vertices[i]);
	}

	sortPolys();

	for (Triangle* poly : m_Polys) {
		poly->render(target, buffer);
	}
}

std::vector<projection::AbstractObject*> projection::Mesh::getChildren()
{
	std::vector<AbstractObject*> outVec;
	for (Point* p : m_Points) {
		outVec.push_back(p);
	}
	return outVec;
}

std::vector<projection::Point*>* projection::Mesh::getPoints()
{
	return &m_Points;
}

void projection::Mesh::sortPolys()
{
	unsigned int swaps = 1;
	while (swaps > 0) {
		swaps = 0;
		for (int i = 0; i < m_Polys.size(); i++) {
			if (i + 1.f >= m_Polys.size()) continue;
			if (m_Polys[static_cast<std::vector<Triangle*, std::allocator<Triangle*>>::size_type>(i) + 1]->averageZ() < m_Polys[i]->averageZ()) {
				Triangle* tempPoly = m_Polys[i];
				m_Polys[i] = m_Polys[(int) (i + 1.f)];
				m_Polys[(int) (i + 1.f)] = tempPoly;
				swaps++;
			}
		}
	}
}
