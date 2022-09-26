#pragma once

#include <vector>

#include "Renderable.h"
#include "Triangle.h"
#include "Point.h"
#include "../Textured.h"

namespace projection {
	class Mesh : public Textured
	{
	protected:
		std::vector<Triangle*> polys;
		std::vector<Point*> points;
		Matrix3X1 meshCenter;

		bool wireFrame_;

		void createVert(int p1, int p2, sf::RenderTarget* target);
		void createTriangle(Point* p1, Point* p2, Point* p3, sf::Color color);
		void createTriangle(Point* p1, Point* p2, Point* p3, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_);
		void sortPolys();

	public:
		~Mesh();

		void rotateX(float angle) override;
		void rotateY(float angle) override;
		void rotateZ(float angle) override;

		void rotateX(float angle, sf::Vector3f refPosition) override;
		void rotateY(float angle, sf::Vector3f refPosition) override;
		void rotateZ(float angle, sf::Vector3f refPosition) override;

		void rotateByCamera(float angle, sf::Vector3f refPosition) override;

		void moveByValue(sf::Vector3f dir) override;
		void moveToPos(sf::Vector3f pos) override;

		void setGlobalOffset(sf::Vector3f* vec) override;

		void applyPerspective() override;
		void virtual connect(sf::RenderTarget* target) = 0;

		virtual void render(sf::RenderTarget* target, sf::Uint8* buffer = nullptr);

		std::vector<AbstractObject*> getChildren() override;
	
		std::vector<Point*>* getPoints();
	};
}


