#pragma once

#include <vector>

#include "Renderable.h"

class RenderQueue
{
private:
	std::vector<Renderable*> renderQueue;
	sf::Vector3f* globalOffset;

public:
	RenderQueue(sf::Vector3f* globalOffset);
	~RenderQueue();

	void applyPerspective(float distance);
	void renderAll(sf::RenderTarget* target);
	void renderByAdress(Renderable* obj, sf::RenderTarget* target);

	void addObject(Renderable* obj);
	bool removeObject(Renderable* obj);

	void moveCamera(sf::Vector3f dirVec);
	void moveCameraOnAngle(sf::Vector2f dirVec);
};

