#pragma once

// Frontend
#include "../gui/GUI.h"
#include <corecrt_memory.h>

// SFML Graphics Framework
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>

// Engine Components
#include "../object/renderable/Point.h"
#include "../object/renderable/Cube.h"
#include "../object/renderable/Triangle.h"
#include "../object/renderable/WavefrontObj.h"
#include "../object/Camera.h"

#include "renderer/Pipeline.h"

#include "ObjectHandler.h"

// Config file
#include "../misc/config.hpp"

namespace projection {
	class Game
	{
	private:
		// Variables
		std::string windowTitle = "Window";
		bool drawAll_;

		// Window
		sf::RenderWindow* window;
		sf::Event ev;
		sf::VideoMode videoMode;

		float dt_;
		float movementCamera_;

		sf::Clock clock;

		// Private functions
		void initVariables();
		void initWindow();
		void initGameObjects();
		void initPipeline();

		void updateGameObjects();
		void updateGUI();

		void setTitle();

		// Game objects
		Pipeline* pl;
		Camera* camera;

		ObjectHandler* objHandler;

		GUI* GUI_;

		WavefrontObj* obj = new WavefrontObj();

	public:
		// Constructors
		Game();
		virtual ~Game();

		// Accessors
		const bool getWindowIsOpen() const;

		// Functions
		void pollEvents();
		void update();
		void render();
	};
}


