#include "Triangle.h"

Triangle::Triangle(Point* p1, Point* p2, Point* p3, sf::Color color, std::string name)
{
	isTextured = false;
	texture = nullptr;
	name_ = name;

	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	this->color = color;
}

Triangle::Triangle(Point* p1, Point* p2, Point* p3, Texture* texture, std::string name, sf::Vector2f texCord1_, sf::Vector2f texCord2_, sf::Vector2f texCord3_)
{
	isTextured = true;
	this->texture = texture;
	textureArr = texture->getPixelPtr();
	dimRef = texture->getSize();

	name_ = name;

	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;

	this->texCord1_ = texCord1_;
	this->texCord2_ = texCord2_;
	this->texCord3_ = texCord3_;

	this->color = color;
}

Triangle::~Triangle()
{
	if (deletePointsOnDestruction) {
		delete p1;
		delete p2;
		delete p3;
	}
}

void Triangle::applyPerspective()
{
	p1->applyPerspective();
	p2->applyPerspective();
	p3->applyPerspective();
}

void Triangle::render(sf::RenderTarget* target, sf::Uint8* buffer)
{
	// Catch if triangle is out of screen
	bool temp = isOutsideScreen(target);
	if (temp) return;

	if (calculateProjectedZ() < 0.f) {
		if (isTextured) {
			// Sort points in y order
			Point* tempPoint;
			sf::Vector2f tempCord;

			if (p1->getScreenPosition(target).y > p2->getScreenPosition(target).y) {
				tempPoint = p1;
				p1 = p2;
				p2 = tempPoint;

				tempCord = texCord1_;
				texCord1_ = texCord2_;
				texCord2_ = tempCord;
			}
			if (p1->getScreenPosition(target).y > p3->getScreenPosition(target).y) {
				tempPoint = p1;
				p1 = p3;
				p3 = tempPoint;

				tempCord = texCord1_;
				texCord1_ = texCord3_;
				texCord3_ = tempCord;
			}
			if (p2->getScreenPosition(target).y > p3->getScreenPosition(target).y) {
				tempPoint = p2;
				p2 = p3;
				p3 = tempPoint;

				tempCord = texCord2_;
				texCord2_ = texCord3_;
				texCord3_ = tempCord;
			}

			sf::Vector2f texCord1{};
			sf::Vector2f texCord2{};
			sf::Vector2f texCord3{};

			texCord1.x = p1->applyPerspCorr(texCord1_.x);
			texCord1.y = p1->applyPerspCorr(texCord1_.y);

			texCord2.x = p2->applyPerspCorr(texCord2_.x);
			texCord2.y = p2->applyPerspCorr(texCord2_.y);

			texCord3.x = p3->applyPerspCorr(texCord3_.x);
			texCord3.y = p3->applyPerspCorr(texCord3_.y);
			
			sf::Vector2f pos1 = p1->getScreenPosition(target);
			sf::Vector2f pos2 = p2->getScreenPosition(target);
			sf::Vector2f pos3 = p3->getScreenPosition(target);

			float w1 = p1->getW();
			float w2 = p2->getW();
			float w3 = p3->getW();

			int texWidth = texture->getSize().x;
			int texHeight = texture->getSize().y;

			// Top triangle of polygon
			if (pos1.y < pos2.y) {
				float slope1 = (pos2.x - pos1.x) / (pos2.y - pos1.y);
				float slope2 = (pos3.x - pos1.x) / (pos3.y - pos1.y);
				int rowsRendered = pos2.y;
				clamp<int>(0, &rowsRendered, c_winHeight);

				for (int i = 0; i <= rowsRendered - pos1.y; i++) {
					// Calculate start and end x-position
					int x1 = (int)(pos1.x + i * slope1);
					int x2 = (int)(pos1.x + i * slope2);
					int y = (int)(pos1.y + i);

					if (y < 0 || y >= c_winHeight) continue;

					float us = texCord1.x + ((float)y - pos1.y) / (pos2.y - pos1.y) * (texCord2.x - texCord1.x);
					float vs = texCord1.y + ((float)y - pos1.y) / (pos2.y - pos1.y) * (texCord2.y - texCord1.y);
					float ws = w1 +			((float)y - pos1.y) / (pos2.y - pos1.y) * (w2 - w1);

					float ue = texCord1.x + ((float)y - pos1.y) / (pos3.y - pos1.y) * (texCord3.x - texCord1.x);
					float ve = texCord1.y + ((float)y - pos1.y) / (pos3.y - pos1.y) * (texCord3.y - texCord1.y);
					float we = w1 +		    ((float)y - pos1.y) / (pos3.y - pos1.y) * (w3 - w1);

					// Sort values
					if (x1 > x2) {
						int tempInt = x1;
						x1 = x2;
						x2 = tempInt;

						float tempFloat = us;
						us = ue;
						ue = tempFloat;

						tempFloat = vs;
						vs = ve;
						ve = tempFloat;

						tempFloat = ws;
						ws = we;
						we = tempFloat;
					}

					if (x2 > x1) {
						// Draw to buffer
						float u = us * texWidth;
						float uStep = (ue - us) / (x2 - x1) * texWidth;
						float v = vs * texHeight;
						float vStep = (ve - vs) / (x2 - x1) * texHeight;
						float w = ws;
						float wStep = (we - ws) / (x2 - x1);

						register unsigned int uI;
						register unsigned int vI;

						for (register int j = x1; j <= x2; j++) {
							u += uStep;
							v += vStep;
							w += wStep;

							uI = (unsigned int)(u / w);
							vI = (unsigned int)(v / w);

							if (j >= 0 && j < c_winWidth && y >= 0 && y < c_winHeight) {
								buffer[(c_winWidth * y + j) * 4] = *(getPixelPtr(uI, vI));
								buffer[(c_winWidth * y + j) * 4 + 1] = *(getPixelPtr(uI, vI) + 1);
								buffer[(c_winWidth * y + j) * 4 + 2] = *(getPixelPtr(uI, vI) + 2);
								buffer[(c_winWidth * y + j) * 4 + 3] = *(getPixelPtr(uI, vI) + 3);
							}
						}
					}
				}
			}

			// Bottom triangle of polygon
			if (pos2.y < pos3.y) {
				float slope1 = (pos3.x - pos2.x) / (pos3.y - pos2.y);
				float slope2 = (pos3.x - pos1.x) / (pos3.y - pos1.y);
				float sx = pos3.x - (pos3.y - pos2.y) * slope2;
				int rowsRendered = pos3.y;
				clamp<int>(0, &rowsRendered, c_winHeight);

				for (int i = 0; i <= rowsRendered - pos2.y; i++) {
					// Calculate start and end x-position
					int x1 = (int)(pos2.x + i * slope1);
					int x2 = (int)(sx + i * slope2);
					int y = (int)(pos2.y + i);

					if (y < 0 || y >= c_winHeight) continue;

					float us = texCord2.x + ((float)y - pos2.y) / (pos3.y - pos2.y) * (texCord3.x - texCord2.x);
					float vs = texCord2.y + ((float)y - pos2.y) / (pos3.y - pos2.y) * (texCord3.y - texCord2.y);
					float ws = w2 + ((float)y - pos2.y) / (pos3.y - pos2.y) * (w3 - w2);

					float ue = texCord1.x + ((float)y - pos1.y) / (pos3.y - pos1.y) * (texCord3.x - texCord1.x);
					float ve = texCord1.y + ((float)y - pos1.y) / (pos3.y - pos1.y) * (texCord3.y - texCord1.y);
					float we = w1 + ((float)y - pos1.y) / (pos3.y - pos1.y) * (w3 - w1);

					// Sort values
					if (x1 > x2) {
						int tempInt = x1;
						x1 = x2;
						x2 = tempInt;

						float tempFloat = us;
						us = ue;
						ue = tempFloat;

						tempFloat = vs;
						vs = ve;
						ve = tempFloat;

						tempFloat = ws;
						ws = we;
						we = tempFloat;
					}

					if (x2 > x1) {
						// Draw to buffer
						float u = us * texWidth;
						float uStep = (ue - us) / (x2 - x1) * texWidth;
						float v = vs * texHeight;
						float vStep = (ve - vs) / (x2 - x1) * texHeight;
						float w = ws;
						float wStep = (we - ws) / (x2 - x1);

						register unsigned int uI;
						register unsigned int vI;

						for (register int j = x1; j <= x2; j++) {
							u += uStep;
							v += vStep;
							w += wStep;

							uI = (unsigned int)(u / w);
							vI = (unsigned int)(v / w);

							if (j >= 0 && j < c_winWidth && y >= 0 && y < c_winHeight) {
								buffer[(c_winWidth * y + j) * 4] = *(getPixelPtr(uI, vI));
								buffer[(c_winWidth * y + j) * 4 + 1] = *(getPixelPtr(uI, vI) + 1);
								buffer[(c_winWidth * y + j) * 4 + 2] = *(getPixelPtr(uI, vI) + 2);
								buffer[(c_winWidth * y + j) * 4 + 3] = *(getPixelPtr(uI, vI) + 3);
							}
						}
					}
				}
			}
		}
		else if (!isTextured) {
			createPoly(target);
			target->draw(vertices[0]);
		}
	}
}

void Triangle::moveByValue(sf::Vector3f dir)
{
	p1->moveByValue(dir);
	p2->moveByValue(dir);
	p3->moveByValue(dir);
}

void Triangle::moveToPos(sf::Vector3f pos)
{
	p1->moveToPos(pos);
	p2->moveToPos(pos);
	p3->moveToPos(pos);
}

void Triangle::rotateX(float angle)
{
	p1->rotateX(angle);
	p2->rotateX(angle);
	p3->rotateX(angle);
}

void Triangle::rotateY(float angle)
{
	p1->rotateY(angle);
	p2->rotateY(angle);
	p3->rotateY(angle);
}

void Triangle::rotateZ(float angle)
{
	p1->rotateZ(angle);
	p2->rotateZ(angle);
	p3->rotateZ(angle);
}

void Triangle::rotateX(float angle, sf::Vector3f refPosition)
{
	p1->rotateX(angle, refPosition);
	p2->rotateX(angle, refPosition);
	p3->rotateX(angle, refPosition);
}

void Triangle::rotateY(float angle, sf::Vector3f refPosition)
{
	p1->rotateY(angle, refPosition);
	p2->rotateY(angle, refPosition);
	p3->rotateY(angle, refPosition);
}

void Triangle::rotateZ(float angle, sf::Vector3f refPosition)
{
	p1->rotateZ(angle, refPosition);
	p2->rotateZ(angle, refPosition);
	p3->rotateZ(angle, refPosition);
}

void Triangle::setGlobalOffset(sf::Vector3f* vec)
{
	this->globalOffset_ = vec;
}

const bool Triangle::isOutsideScreen(sf::RenderTarget* target) const
{
	std::vector<sf::Vector2f> points{ p1->getScreenPosition(target) , p2->getScreenPosition(target) , p3->getScreenPosition(target) };
	sf::Vector2u scrSize{target->getSize().x, target->getSize().y};
	
	// Exit if one point is inside
	if ((points[0].x >= 0 && points[0].x < scrSize.x && points[0].y >= 0 && points[0].y < scrSize.y) ||
		(points[1].x >= 0 && points[1].x < scrSize.x && points[1].y >= 0 && points[1].y < scrSize.y) ||
		(points[2].x >= 0 && points[2].x < scrSize.x && points[2].y >= 0 && points[2].y < scrSize.y)) {
		return false;
	}

	auto isOutside = [](sf::Vector2f p0, sf::Vector2f p1, sf::Vector2u scrSize) {
		auto cutsEdge = [](float edge0) {
			return edge0 >= 0.f && edge0 <= 1.f;
		};

		sf::Vector2f direction = p1 - p0;
		/*if ((int)direction.x == 0) direction.x = 0.000001f;		// No check for 0 division, but float conversion results in small number
		if ((int)direction.y == 0) direction.y = 0.000001f;*/		//

		float Ty0 = -p0.y / direction.y;
		float Tx0 = -p0.x / direction.x;
		float TyS = (scrSize.y - p0.y) / direction.y;
		float TxS = (scrSize.x - p0.x) / direction.x;

		// Check if edge intersections are at important poisitions
		if (cutsEdge(Ty0)) {
			float xCut = p0.x + direction.x * Ty0;
			if (xCut < 0.f || xCut > scrSize.x) Ty0 = -1.f;
		}
		if (cutsEdge(Tx0)) {
			float yCut = p0.y + direction.y * Tx0;
			if (yCut < 0.f || yCut > scrSize.y) Tx0 = -1.f;
		}
		if (cutsEdge(TyS)) {
			float xCut = p0.x + direction.x * TyS;
			if (xCut < 0.f || xCut > scrSize.x) TyS = -1.f;
		}
		if (cutsEdge(TxS)) {
			float yCut = p0.y + direction.y * TxS;
			if (yCut < 0.f || yCut > scrSize.y) TxS = -1.f;
		}

		// Check if screen cut is between points ( 0.f < t < 1.f )
		// Check for each edge
		if (cutsEdge(Tx0) && cutsEdge(Ty0) ||
			cutsEdge(Tx0) && cutsEdge(TxS) ||
			cutsEdge(Tx0) && cutsEdge(TyS) ||
			cutsEdge(Ty0) && cutsEdge(TyS) ||
			cutsEdge(Ty0) && cutsEdge(TxS) ||
			cutsEdge(TxS) && cutsEdge(TyS)) {
			return false;
		}
		return true;
	};

	bool v0 = isOutside(points[0], points[1], scrSize);
	bool v1 = isOutside(points[0], points[2], scrSize);
	bool v2 = isOutside(points[1], points[2], scrSize);
	
	if (v0 && v1 && v2) return true;
	else return false;	
}

std::vector<AbstractObject*> Triangle::getChildren()
{
	std::vector<AbstractObject*> outVec;
	outVec.push_back(p1);
	outVec.push_back(p2);
	outVec.push_back(p3);
	return outVec;
}

double Triangle::averageZ()
{
	return (p1->getPosition().z + p2->getPosition().z + p3->getPosition().z) / 3.f;
}

double Triangle::calculateProjectedZ()
{
	sf::Vector3f proj1 = p1->getProjPosition();
	sf::Vector3f proj2 = p2->getProjPosition();
	sf::Vector3f proj3 = p3->getProjPosition();

	sf::Vector3f p1p2 = (p2->getProjPosition() - p1->getProjPosition());
	sf::Vector3f p1p3 = (p3->getProjPosition() - p1->getProjPosition());

	p1p2.z = 0.f;
	p1p3.z = 0.f;

	return p1p2.x * p1p3.y - p1p2.y * p1p3.x;
}

void Triangle::setTexCord(unsigned int point, sf::Vector2f cord)
{
	switch (point) {
	case 1: {
		texCord1_ = cord;
		break;
	}
	case 2: {
		texCord2_ = cord;
		break;
	}
	case 3: {
		texCord3_ = cord;
		break;
	}
	default: {
		return;
	}
	}
}

sf::Vector2f Triangle::getTexCord(unsigned int point)
{
	switch (point) {
	case 1: {
		return texCord1_;
	}
	case 2: {
		return texCord2_;
	}
	case 3: {
		return texCord3_;
	}
	default: {
		return sf::Vector2f();
	}
	}
}

void Triangle::createPoly(sf::RenderTarget* target)
{
	vertices.clear();

	sf::VertexArray poly(sf::Triangles, 3);
	poly[0].position = translateToRel(sf::Vector2f(p1->getProjMatrix()->x0, p1->getProjMatrix()->y0), target->getSize());
	poly[1].position = translateToRel(sf::Vector2f(p2->getProjMatrix()->x0, p2->getProjMatrix()->y0), target->getSize());
	poly[2].position = translateToRel(sf::Vector2f(p3->getProjMatrix()->x0, p3->getProjMatrix()->y0), target->getSize());

	poly[0].color = color;
	poly[1].color = color;
	poly[2].color = color;

	vertices.push_back(poly);
}
