#include "RenderQueue.h"

projection::RenderQueue::RenderQueue(sf::Vector3f* globalOffset_)
{
	this->globalOffset_ = globalOffset_;
}

projection::RenderQueue::~RenderQueue()
{
	for (Renderable* r : renderQueue) {
		delete r;
	}
}

void projection::RenderQueue::setCamera(Camera* camera)
{
	this->camera = camera;
	globalOffset_ = camera->getOffset();
}

void projection::RenderQueue::applyPerspective()
{
	for (Renderable* renderObj : renderQueue) {
		renderObj->applyPerspective();
	}
}

void projection::RenderQueue::renderAll(sf::RenderTarget* target, sf::Texture* textureBuffer, sf::Sprite* sprtBuffer, sf::Uint8* buffer)
{
	if (camera) {
		// Clear screen buffer
		memset(buffer, 0, c_winHeight * c_winWidth * 4);

		for (Renderable* renderObj : renderQueue) {
			renderObj->render(target, buffer);
		}

		// Display buffer
		textureBuffer->update(buffer);
		target->draw(*sprtBuffer);
	}
}

void projection::RenderQueue::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	if (camera) {
		for (Renderable* renderObj : renderQueue) {
			if (renderObj = obj) renderObj->render(target);
		}
	}
}

void projection::RenderQueue::addObject(Renderable* obj)
{
	renderQueue.push_back(obj);
	obj->setGlobalOffset(globalOffset_);
}

bool projection::RenderQueue::removeObject(Renderable* obj)
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
