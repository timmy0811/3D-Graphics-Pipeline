#include "Plane.h"

projection::Plane::Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, sf::Color color)
{
	m_IsTextured = false;
	name_ = name;
	this->m_Target = target;
	this->m_Color = color;

	m_MeshCenter.x0 = position.x + size.x / 2.f;
	m_MeshCenter.y0 = position.y;
	m_MeshCenter.z0 = position.z + size.y / 2.f;

	m_ScaleAbsolute.x = size.x;
	m_ScaleAbsolute.y = 0.f;
	m_ScaleAbsolute.z = size.y;

	m_PosX = &position.x;
	m_PosY = &position.y;
	m_PosZ = &position.z;

	m_Points.push_back(new Point(sf::Vector3f(position.x, position.y,position.z), "point_0"));
	m_Points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z), "point_1"));
	m_Points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z + size.y), "point_2"));
	m_Points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z + size.y), "point_3"));
}

projection::Plane::Plane(sf::Vector3f position, sf::Vector2f size, sf::RenderTarget* target, std::string name, Texture* texture)
{
	m_IsTextured = true;
	name_ = name;
	this->m_Target = target;
	this->m_Texture = texture;
	this->m_Color = m_Color;

	m_MeshCenter.x0 = position.x + size.x / 2.f;
	m_MeshCenter.y0 = position.y;
	m_MeshCenter.z0 = position.z + size.y / 2.f;

	m_ScaleAbsolute.x = size.x;
	m_ScaleAbsolute.y = 0.f;
	m_ScaleAbsolute.z = size.y;

	m_PosX = &position.x;
	m_PosY = &position.y;
	m_PosZ = &position.z;

	m_Points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z), "point_0"));
	m_Points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z), "point_1"));
	m_Points.push_back(new Point(sf::Vector3f(position.x + size.x, position.y, position.z + size.y), "point_2"));
	m_Points.push_back(new Point(sf::Vector3f(position.x, position.y, position.z + size.y), "point_3"));
}

projection::Plane::~Plane()
{
	Mesh::~Mesh();
}

void projection::Plane::connect(sf::RenderTarget* target)
{
	for (Triangle* poly : m_Polys) {
		delete poly;
	}

	m_Polys.clear();

	if (m_IsTextured) {
		createTriangle(m_Points[0], m_Points[3], m_Points[1], sf::Vector2f(0.f, 0.f), sf::Vector2f(1.f, 0.f), sf::Vector2f(0.f, 1.f));
		createTriangle(m_Points[3], m_Points[2], m_Points[1], sf::Vector2f(1.f, 0.f), sf::Vector2f(1.f, 1.f), sf::Vector2f(0.f, 1.f));
	}
	else {
		createTriangle(m_Points[0], m_Points[3], m_Points[1], m_Color);
		createTriangle(m_Points[3], m_Points[2], m_Points[1], m_Color);
	}
}
