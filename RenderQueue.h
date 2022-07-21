#pragma once

#include <vector>

#include "Renderable.h"
#include "Triangle.h"
#include "Camera.h"
#include "config.h"

class RenderQueue
{
private:
	std::vector<Renderable*> renderQueue;
	sf::Vector3f* globalOffset_;

	Camera* camera;

public:
	RenderQueue(sf::Vector3f* globalOffset_ = new sf::Vector3f());
	~RenderQueue();

	void setCamera(Camera* camera);

	void applyPerspective();
	void renderAll(sf::RenderTarget* target, sf::Texture* textureBuffer, sf::Sprite* sprtBuffer, sf::Uint8* buffer = nullptr);
	void renderByAdress(Renderable* obj, sf::RenderTarget* target);

	void addObject(Renderable* obj);
	bool removeObject(Renderable* obj);
};

