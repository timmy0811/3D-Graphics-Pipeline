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
		RenderQueue* queue;
		Matrix3X3 projection;

		Camera* camera;

		// Screen-Buffer
		sf::Texture textureBuffer;
		sf::Sprite sprtBuffer;

		sf::Uint8* buffer;

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


