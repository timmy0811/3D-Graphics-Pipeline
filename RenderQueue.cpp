#include "RenderQueue.h"

RenderQueue::RenderQueue()
{
	
}

void RenderQueue::renderAll(sf::RenderTarget* target)
{
	for (Renderable* renderObj : renderQueue) {
		renderObj->render(target);
	}
}

void RenderQueue::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	for (Renderable* renderObj : renderQueue) {
		if (renderObj = obj) renderObj->render(target);
	}
}

void RenderQueue::addObject(Renderable* obj)
{
	renderQueue.push_back(obj);
}

bool RenderQueue::removeObject(Renderable* obj)
{
	for (int i = 0; i < renderQueue.size(); i++) {
		if (renderQueue[i] == obj) renderQueue.erase(renderQueue.begin() + i);
	}
}
