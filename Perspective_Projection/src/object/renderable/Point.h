#pragma once

#include <SFML/Graphics.hpp>

#include <vector>

#include "Matrix3X1.h"
#include "MatrixOperations.h"

#include "Renderable.h"

class Point : public Renderable
{
private:
	Matrix3X1 position;
	Matrix3X1 projectedPositon;
	sf::CircleShape shape;

	float w;
	float wProj;

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

