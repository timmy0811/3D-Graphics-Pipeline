#pragma once

#include <vector>

#include "Renderable.h"
#include "Camera.h"

class RenderQueue
{
private:
	std::vector<Renderable*> renderQueue;
	sf::Vector3f* globalOffset;

	Camera* camera;

public:
	RenderQueue(sf::Vector3f* globalOffset = new sf::Vector3f());
	~RenderQueue();

	void setCamera(Camera* camera);

	void applyPerspective(float distance);
	void renderAll(sf::RenderTarget* target);
	void renderByAdress(Renderable* obj, sf::RenderTarget* target);

	void addObject(Renderable* obj);
	bool removeObject(Renderable* obj);
};

