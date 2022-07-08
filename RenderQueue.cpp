#include "RenderQueue.h"

RenderQueue::RenderQueue(sf::Vector3f* globalOffset_)
{
	this->globalOffset_ = globalOffset_;
}

RenderQueue::~RenderQueue()
{
	for (Renderable* r : renderQueue) {
		delete r;
	}
}

void RenderQueue::setCamera(Camera* camera)
{
	this->camera = camera;
	globalOffset_ = camera->getOffset();
}

void RenderQueue::applyPerspective(float distance_)
{
	for (Renderable* renderObj : renderQueue) {
		renderObj->applyPerspective(distance_);
	}
}

void RenderQueue::renderAll(sf::RenderTarget* target)
{
	if (camera) {
		for (Renderable* renderObj : renderQueue) {
			renderObj->render(target);
		}
	}
}

void RenderQueue::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	if (camera) {
		for (Renderable* renderObj : renderQueue) {
			if (renderObj = obj) renderObj->render(target);
		}
	}
}

void RenderQueue::addObject(Renderable* obj)
{
	renderQueue.push_back(obj);
	obj->setGlobalOffset(globalOffset_);
}

bool RenderQueue::removeObject(Renderable* obj)
{
	for (int i = 0; i < renderQueue.size(); i++) {
		if (renderQueue[i] == obj)
		{
			renderQueue.erase(renderQueue.begin() + i);
			return true;
		}
	}
	return false;
}
