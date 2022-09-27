#include "Pipeline.h"

projection::Pipeline::Pipeline()
{
	m_Queue = new RenderQueue();
	m_ProjectionMat = Matrix3X3(0.f, MATRIX_TYPE::PROJECTION);

	// Screen Buffer init
	m_Buffer = new sf::Uint8[c_winHeight * c_winWidth * 4];
	memset(m_Buffer, 0, c_winHeight * c_winWidth * 4);

	m_TextureBuffer.create(c_winWidth, c_winHeight);
	m_SpriteBuffer.setTexture(m_TextureBuffer, true);
}

projection::Pipeline::~Pipeline()
{
	delete m_Queue;
}

void projection::Pipeline::setCamera(Camera* camera)
{
	this->m_Camera = camera;
	m_Queue->setCamera(camera);
}

void projection::Pipeline::renderAll(sf::RenderTarget* target)
{
	m_Queue->applyPerspective();
	m_Queue->renderAll(target,&m_TextureBuffer, &m_SpriteBuffer, m_Buffer);
}

void projection::Pipeline::renderByAdress(Renderable* obj, sf::RenderTarget* target)
{
	m_Queue->renderByAdress(obj, target);
}

void projection::Pipeline::addObjectToQueue(Renderable* obj)
{
	m_Queue->addObject(obj);
}

bool projection::Pipeline::removeObjectFromQueue(Renderable* obj)
{
	return m_Queue->removeObject(obj);
}
