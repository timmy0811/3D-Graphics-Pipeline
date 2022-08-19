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

void RenderQueue::applyPerspective()
{
	for (Renderable* renderObj : renderQueue) {
		renderObj->applyPerspective();
	}
}

void RenderQueue::renderAll(sf::RenderTarget* target, sf::Texture* textureBuffer, sf::Sprite* sprtBuffer, sf::Uint8* buffer)
{
	if (camera) {
		// Clear screen buffer
		memset(buffer, 0, c_winHeight * c_winWidth * 4);

		// general render-queue
		for (Renderable* renderObj : renderQueue) {
			renderObj->render(target, buffer);
		}

		// temporary render queue
		for (Renderable* renderObj : tempQueue) {
			renderObj->render(target, buffer);
		}
		tempQueue.clear();
		tempQueue.shrink_to_fit();

		// Display buffer
		textureBuffer->update(buffer);
		target->draw(*sprtBuffer);
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

void RenderQueue::addTempObject(Renderable* obj)
{
	tempQueue.push_back(obj);
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
