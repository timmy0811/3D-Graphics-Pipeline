#include "Pipeline.h"

projection::Pipeline::Pipeline()
{
	queue = new RenderQueue();
	projection = Matrix3X3(0.f, MATRIX_TYPE::PROJECTION);

	// Screen Buffer init
	buffer = new sf::Uint8[c_winHeight * c_winWidth * 4];
	memset(buffer, 0, c_winHeight * c_winWidth * 4);

	textureBuffer.create(c_winWidth, c_winHeight);
	sprtBuffer.setTexture(textureBuffer, true);
}

projection::Pipeline::~Pipeline()
{
	delete queue;
}

void projection::Pipeline::setCamera(Camera* camera)
{
	this->camera = camera;
	queue->setCamera(camera);
}

void projection::Pipeline::renderAll(sf::RenderTarget* target)
{
	queue->applyPerspective();
	queue->renderAll(target,&textureBuffer, &sprtBuffer, buffer);
}

void projection::Pipeline::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	queue->renderByAdress(obj, target);
}

void projection::Pipeline::addObjectToQueue(Renderable* obj)
{
	queue->addObject(obj);
}

bool projection::Pipeline::removeObjectFromQueue(Renderable* obj)
{
	return queue->removeObject(obj);
}
