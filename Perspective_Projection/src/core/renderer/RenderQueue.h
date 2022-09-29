#pragma once

#include <vector>

#include "../../object/renderable/Renderable.h"
#include "../../object/renderable/Triangle.h"

#include "../../object/Camera.h"

#include "../../misc/config.hpp"

namespace projection {
	class RenderQueue
	{
	private:
		std::vector<Renderable*> m_RenderQueue;
		sf::Vector3f* m_GlobalOffset;

		Camera* m_Camera;

	public:
		RenderQueue(sf::Vector3f* globalOffset_ = new sf::Vector3f());
		~RenderQueue();

		void setCamera(Camera* camera);

		void applyPerspective() const;
		void renderAll(sf::RenderTarget* target, sf::Texture* textureBuffer, sf::Sprite* sprtBuffer, sf::Uint8* buffer = nullptr) const;
		void renderByAdress(Renderable* obj, sf::RenderTarget* target) const;

		void addObject(Renderable* obj);
		bool removeObject(Renderable* obj);
	};
}


