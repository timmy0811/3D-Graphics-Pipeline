#pragma once

#include <vector>

#include "config.h"

// ImGui Frontend
#include "imgui.h"
#include "imgui-SFML.h"

// Dependencies
#include "Point.h"
#include "Cube.h"
#include "Pipeline.h"
#include "Triangle.h"
#include "Camera.h"
#include "AbstractObject.h"

namespace GUI
{
	void menuBar();
	void objectBrowser(std::vector<AbstractObject*> objects);
	void treeChildren(ImGuiTreeNodeFlags node_flags, bool isOpen, AbstractObject* obj);

	void objectAttributes(AbstractObject* obj);
	void diagnosticsWindow(sf::Vector3f* cameraPos, int fps);
};

