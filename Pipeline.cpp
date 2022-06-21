#include "Pipeline.h"

Pipeline::Pipeline()
{
	projection = Matrix3X3(0.f, MATRIX_TYPE::PROJECTION);
}

void Pipeline::renderAll(sf::RenderTarget* target)
{
	queue.renderAll(target);
}

void Pipeline::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	queue.renderByAdress(obj, target);
}

void Pipeline::addObjectToQueue(Renderable* obj)
{
	queue.addObject(obj);
}

bool Pipeline::removeObjectFromQueue(Renderable* obj)
{
	return queue.removeObject(obj);
}
