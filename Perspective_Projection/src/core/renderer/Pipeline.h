#pragma once

#include "../../misc/matrix/Matrix3X1.h"
#include "../../misc/matrix/Matrix3X3.h"

#include "../../object/renderable/Renderable.h"
#include "../../object/Camera.h"
#include "../../object/Texture.h"

#include "../../misc/Ressources.h"

#include "RenderQueue.h"

namespace projection {
	class Pipeline
	{
	private:
		RenderQueue* m_Queue;
		Matrix3X3 m_ProjectionMat;

		Camera* m_Camera;

		// Screen-Buffer
		sf::Texture m_TextureBuffer;
		sf::Sprite m_SpriteBuffer;

		sf::Uint8* m_Buffer;

	public:
		Pipeline();
		~Pipeline();

		void setCamera(Camera* camera);

		void renderAll(sf::RenderTarget* target);
		void renderByAdress(Renderable* obj, sf::RenderTarget* target);

		void addObjectToQueue(Renderable* obj);
		bool removeObjectFromQueue(Renderable* obj);
	};
}


