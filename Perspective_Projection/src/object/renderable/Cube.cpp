#include "Cube.h"

void projection::Cube::init(sf::Vector3f position, float size)
{
	m_MeshCenter.x0 = position.x + size / 2.f;
	m_MeshCenter.y0 = position.y + size / 2.f;
	m_MeshCenter.z0 = position.z + size / 2.f;

	m_Points.push_back(new Point(sf::Vector3f(size + position.x, 0.f + position.y, 0.f + position.z), "point_0"));
	m_Points.push_back(new Point(sf::Vector3f(0.f + position.x, size + position.y, 0.f + position.z), "point_1"));
	m_Points.push_back(new Point(sf::Vector3f(size + position.x, size + position.y, 0.f + position.z), "point_2"));
	m_Points.push_back(new Point(sf::Vector3f(0.f + position.x, 0.f + position.y, 0.f + position.z), "point_3"));

	m_Points.push_back(new Point(sf::Vector3f(size + position.x, 0.0f + position.y, size + position.z), "point_4"));
	m_Points.push_back(new Point(sf::Vector3f(0.f + position.x, size + position.y, size + position.z), "point_5"));
	m_Points.push_back(new Point(sf::Vector3f(size + position.x, size + position.y, size + position.z), "point_6"));
	m_Points.push_back(new Point(sf::Vector3f(0.f + position.x, 0.f + position.y, size + position.z), "point_7"));

	m_PosX = new float;
	m_PosY = new float;
	m_PosZ = new float;

	*m_PosX = position.x;
	*m_PosY = position.x;
	*m_PosZ = position.x;
}

projection::Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name)
{
	m_IsTextured = false;
	wireFrame_ = true;
	name_ = name;
	this->m_Target = target;

	init(position, size);
}

projection::Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, sf::Color color)
{
	m_IsTextured = false;
	wireFrame_ = false;
	this->m_Color = color;
	name_ = name;
	this->m_Target = target;

	init(position, size);
}

projection::Cube::Cube(sf::Vector3f position, float size, sf::RenderTarget* target, std::string name, Texture* texture)
{
	m_IsTextured = true;
	wireFrame_ = false;
	this->m_Texture = texture;
	name_ = name;
	this->m_Target = target;

	init(position, size);
}

projection::Cube::~Cube()
{
	Mesh::~Mesh();
}

void projection::Cube::connect(sf::RenderTarget* target)
{
	for (Triangle* poly : m_Polys) {
		delete poly;
	}

	m_Polys.clear();

	if (wireFrame_) {
		m_Vertices.clear();

		createVert(1, 3, target);
		createVert(1, 2, target);
		createVert(2, 0, target);
		createVert(3, 0, target);

		createVert(3, 7, target);
		createVert(0, 4, target);
		createVert(2, 6, target);
		createVert(1, 5, target);

		createVert(7, 4, target);
		createVert(7, 5, target);
		createVert(5, 6, target);
		createVert(6, 4, target);
	}
	else if(m_IsTextured) {
		createTriangle(m_Points[3], m_Points[2], m_Points[1], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(m_Points[0], m_Points[2], m_Points[3], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(m_Points[7], m_Points[5], m_Points[6], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(m_Points[7], m_Points[6], m_Points[4], sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(m_Points[3], m_Points[7], m_Points[4], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f));
		createTriangle(m_Points[3], m_Points[4], m_Points[0], sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(m_Points[5], m_Points[3], m_Points[1], sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(m_Points[5], m_Points[7], m_Points[3], sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f));

		createTriangle(m_Points[5], m_Points[1], m_Points[6], sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 0.f));
		createTriangle(m_Points[1], m_Points[2], m_Points[6], sf::Vector2f(0.f, 1.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f));

		createTriangle(m_Points[0], m_Points[4], m_Points[6], sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(m_Points[2], m_Points[0], m_Points[6], sf::Vector2f(1.f, 1.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f));
	}
	else {
		createTriangle(m_Points[3], m_Points[2], m_Points[1], m_Color);
		createTriangle(m_Points[0], m_Points[2], m_Points[3], m_Color);

		createTriangle(m_Points[7], m_Points[5], m_Points[6], m_Color);
		createTriangle(m_Points[4], m_Points[7], m_Points[6], m_Color);

		createTriangle(m_Points[3], m_Points[7], m_Points[4], m_Color);
		createTriangle(m_Points[0], m_Points[3], m_Points[4], m_Color);

		createTriangle(m_Points[5], m_Points[3], m_Points[1], m_Color);
		createTriangle(m_Points[7], m_Points[3], m_Points[5], m_Color);

		createTriangle(m_Points[5], m_Points[1], m_Points[6], m_Color);
		createTriangle(m_Points[1], m_Points[2], m_Points[6], m_Color);

		createTriangle(m_Points[0], m_Points[4], m_Points[6], m_Color);
		createTriangle(m_Points[2], m_Points[0], m_Points[6], m_Color);
	}
}
