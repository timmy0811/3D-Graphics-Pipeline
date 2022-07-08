#include "Pipeline.h"

Pipeline::Pipeline(float distance_)
{
	queue = new RenderQueue();
	this->distance_ = distance_;
	projection = Matrix3X3(0.f, MATRIX_TYPE::PROJECTION);
}

Pipeline::~Pipeline()
{
	delete queue;
}

void Pipeline::setCamera(Camera* camera)
{
	this->camera = camera;
	queue->setCamera(camera);
}

void Pipeline::renderAll(sf::RenderTarget* target)
{
	queue->applyPerspective(distance_);
	queue->renderAll(target);
}

void Pipeline::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	queue->renderByAdress(obj, target);
}

void Pipeline::addObjectToQueue(Renderable* obj)
{
	queue->addObject(obj);
}

bool Pipeline::removeObjectFromQueue(Renderable* obj)
{
	return queue->removeObject(obj);
}
