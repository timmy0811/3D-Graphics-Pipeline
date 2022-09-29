#include "RenderQueue.h"

projection::RenderQueue::RenderQueue(sf::Vector3f* globalOffset_)
{
	this->m_GlobalOffset = globalOffset_;
}

projection::RenderQueue::~RenderQueue()
{
	for (Renderable* r : m_RenderQueue) {
		delete r;
	}
}

void projection::RenderQueue::setCamera(Camera* camera)
{
	this->m_Camera = camera;
	m_GlobalOffset = camera->getOffset();
}

void projection::RenderQueue::applyPerspective() const
{
	for (Renderable* renderObj : m_RenderQueue) {
		renderObj->applyPerspective();
	}
}

void projection::RenderQueue::renderAll(sf::RenderTarget* target, sf::Texture* textureBuffer, sf::Sprite* sprtBuffer, sf::Uint8* buffer) const
{
	if (m_Camera) {
		// Clear screen buffer
		memset(buffer, 0, c_winHeight * c_winWidth * 4);

		for (Renderable* renderObj : m_RenderQueue) {
			renderObj->render(target, buffer);
		}

		// Display buffer
		textureBuffer->update(buffer);
		target->draw(*sprtBuffer);
	}
}

void projection::RenderQueue::renderByAdress(Renderable* obj, sf::RenderTarget* target) const
{
	if (m_Camera) {
		for (Renderable* renderObj : m_RenderQueue) {
			if (renderObj = obj) renderObj->render(target);
		}
	}
}

void projection::RenderQueue::addObject(Renderable* obj)
{
	m_RenderQueue.push_back(obj);
	obj->setGlobalOffset(m_GlobalOffset);
}

bool projection::RenderQueue::removeObject(Renderable* obj)
{
	for (int i = 0; i < m_RenderQueue.size(); i++) {
		if (m_RenderQueue[i] == obj)
		{
			m_RenderQueue.erase(m_RenderQueue.begin() + i);
			return true;
		}
	}
	return false;
}
