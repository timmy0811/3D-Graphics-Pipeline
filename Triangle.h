#pragma once

#include "Renderable.h"
#include "Point.h"
#include "Textured.h"

class Triangle : public Textured
{
private:
	Point* p1;
	Point* p2;
	Point* p3;

	sf::Vector2f texCord1_;
	sf::Vector2f texCord2_;
	sf::Vector2f texCord3_;

public:
	Triangle(Point* p1, Point* p2, Point* p3, sf::Color color, std::string name);
	Triangle(Point* p1, Point* p2, Point* p3, Texture* texture, std::string name, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_);

	void applyPerspective() override;
	void render(sf::RenderTarget* target, sf::Uint8* buffer = nullptr) override;

	void moveByValue(sf::Vector3f dir) override;
	void moveToPos(sf::Vector3f pos) override;

	void rotateX(float angle) override;
	void rotateY(float angle) override;
	void rotateZ(float angle) override;

	void rotateX(float angle, sf::Vector3f refPosition) override;
	void rotateY(float angle, sf::Vector3f refPosition) override;
	void rotateZ(float angle, sf::Vector3f refPosition) override;

	void setGlobalOffset(sf::Vector3f* vec) override;

	std::vector<AbstractObject*> getChildren() override;

	double averageZ();
	double calculateProjectedZ();

	void setTexCord(unsigned int point, sf::Vector2f cord);
	sf::Vector2f getTexCord(unsigned int point);

	void createPoly(sf::RenderTarget* target);
};

