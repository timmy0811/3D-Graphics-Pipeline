#pragma once

#include "Matrix3X1.h"
#include "Matrix3X3.h"

#include "Renderable.h"
#include "RenderQueue.h"

class Pipeline
{
private:
	RenderQueue* queue;
	Matrix3X3 projection;

	float distance;

public:
	Pipeline(float distance);
	~Pipeline();

	void renderAll(sf::RenderTarget* target);
	void renderByAdress(Renderable* obj, sf::RenderTarget* target);

	void addObjectToQueue(Renderable* obj);
	bool removeObjectFromQueue(Renderable* obj);
};

