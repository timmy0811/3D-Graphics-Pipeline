#pragma once

#include <vector>

#include "../misc/config.hpp"

// ImGui Frontend
#include "imgui.h"
#include "imgui-SFML.h"

// Dependencies
#include "../core/renderer/Pipeline.h"
#include "../core/ObjectHandler.h"

#include "../object/renderable/Point.h"
#include "../object/renderable/Cube.h"
#include "../object/renderable/Triangle.h"
#include "../object/AbstractObject.h"
#include "../object/Camera.h"

namespace projection {
	class GUI
	{
	private:
		sf::Vector3f m_Position;
		sf::Vector3f m_Scale;
		sf::Vector3f m_Rotation;

		sf::Sprite* m_Sprite;
		std::string m_Name;

		//const char* textureItems[];
		//static const char* currentItem;

		std::vector<AbstractObject*> m_Objects;
		std::vector<Texture*>* m_Textures;

		ObjectHandler* m_Handler;

		void update(AbstractObject* obj);
		void apply(AbstractObject* obj) const;

		void updateBrowser();

		void treeChildren(ImGuiTreeNodeFlags node_flags, bool isOpen, AbstractObject* obj) const;

	public:
		GUI(ObjectHandler* objHandler);

		void menuBar() const;
		void objectBrowser() const;

		void objectAttributes();
		void diagnosticsWindow(sf::Vector3f* cameraPos, int fps) const;
	};
}


