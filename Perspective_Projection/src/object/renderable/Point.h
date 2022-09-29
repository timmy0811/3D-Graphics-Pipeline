#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "../../misc/matrix/Matrix3X1.h"
#include "../../misc/matrix/MatrixOperations.h"

#include "Renderable.h"

namespace projection {
	class Point : public Renderable
	{
	private:
		Matrix3X1 m_Position;
		Matrix3X1 m_PositionProjected;
		sf::CircleShape m_Shape;

		float m_W;
		float m_wProjected;

		void rotateByEnum(float angle, sf::Vector3f refPosition, MATRIX_TYPE type);

	public:
		Point(sf::Vector3f position, std::string name, Matrix3X1* parentPos = nullptr);

		void render(sf::RenderTarget* target, sf::Uint8* buffer = nullptr) override;
		void applyPerspective() override;

		void moveByValue(sf::Vector3f dir) override;
		void moveToPos(sf::Vector3f pos) override;

		void setMatrix(Matrix3X1 mat);
		void setProjMatrix(Matrix3X1 mat);

		Matrix3X1* getMatrix();
		Matrix3X1* getProjMatrix();

		sf::Vector3f getPosition();
		sf::Vector3f getProjPosition();

		float getW();

		sf::Vector2f getScreenPosition(sf::RenderTarget* target);

		void rotateX(float angle) override;
		void rotateY(float angle) override;
		void rotateZ(float angle) override;

		void rotateX(float angle, sf::Vector3f refPosition) override;
		void rotateY(float angle, sf::Vector3f refPosition) override;
		void rotateZ(float angle, sf::Vector3f refPosition) override;

		void rotateByCamera(float angle, sf::Vector3f refPosition) override;

		std::vector<Point*>* getPoints();

		float applyPerspCorr(float v);
	};
}


