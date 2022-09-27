#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <iostream>

#include "../object/renderable/Cube.h"
#include "../object/renderable/Plane.h"
#include "../object/renderable/WavefrontObj.h"

#include "renderer/Pipeline.h"

namespace projection {
	class ObjectHandler
	{
	private:
		// Rigids
		std::vector<Cube*> m_Cubes;
		std::vector<Point*> m_Points;
		std::vector<Triangle*> m_Polys;
		std::vector<Plane*> m_Planes;

		// Textures
		std::vector<Texture*> m_Textures;

		Pipeline* m_Pipeline;
		Camera* m_Camera;
		sf::RenderTarget* m_Target;

		AbstractObject* m_ActiveObject;

		// Ressources;
		Ressources* m_Ressources;

	public:
		ObjectHandler(Pipeline* pipeLine, Camera* camera, sf::RenderTarget* target);
		~ObjectHandler();

		// Cube
		Cube* createCube(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);
		Cube* createCube(sf::Color color, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);
		Cube* createCube(Texture* texture, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), float size = .2f);

		// Point
		Point* createPoint(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f));

		// Poly
		Triangle* createPoly(sf::Color color = sf::Color::Magenta,
			sf::Vector3f position1 = sf::Vector3f(0.5f, 0.f, 0.f),
			sf::Vector3f position2 = sf::Vector3f(0.25f, -0.5f, 0.f),
			sf::Vector3f position3 = sf::Vector3f(0.f, 0.f, 0.f));
		Triangle* createPoly(Texture* texture, 
			sf::Vector3f position1 = sf::Vector3f(0.25f, -0.5f, 0.f), 
			sf::Vector3f position2 = sf::Vector3f(0.f, 0.f, 0.f),
			sf::Vector3f position3 = sf::Vector3f(0.5f, 0.f, 0.f));

		// Texture
		Texture* createTexture(TexType texture);

		// Plane
		Plane* createPlane(sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), sf::Vector2f scale = sf::Vector2f(1.f, 1.f), sf::Color color = sf::Color::White);
		Plane* createPlane(Texture* texture, sf::Vector3f position = sf::Vector3f(0.f, 0.f, 0.f), sf::Vector2f scale = sf::Vector2f(1.f, 1.f));

		std::vector<AbstractObject*>* getObjects() const;
		std::vector<Renderable*> getRenderObjects() const;
		std::vector<Texture*>* getTextures();
		AbstractObject* getActiveObj() const;

		void test_rotate(float dt);
	};
}


