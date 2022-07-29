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
#include "ObjectHandler.h"

class GUI
{
private:
	sf::Vector3f position;
	sf::Vector3f scale;
	sf::Vector3f rotation;

	sf::Sprite* sprt;
	std::string name;

	//const char* textureItems[];
	//static const char* currentItem;

	std::vector<AbstractObject*> objects;
	std::vector<Texture*>* textures;

	ObjectHandler* Handler;

	void update(AbstractObject* obj);
	void apply(AbstractObject* obj);

	void updateBrowser();

	void treeChildren(ImGuiTreeNodeFlags node_flags, bool isOpen, AbstractObject* obj);

public:
	GUI(ObjectHandler* objHandler);

	void menuBar();
	void objectBrowser();

	void objectAttributes();
	void diagnosticsWindow(sf::Vector3f* cameraPos, int fps);
};

