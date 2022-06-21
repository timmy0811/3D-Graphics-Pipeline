#pragma once

#include <vector>

#include "Renderable.h"

class RenderQueue
{
private:
	std::vector<Renderable*> renderQueue;

public:
	RenderQueue();

	void renderAll(sf::RenderTarget* target);
	void renderByAdress(Renderable* obj, sf::RenderTarget* target);

	void addObject(Renderable* obj);
	bool removeObject(Renderable* obj);
};

