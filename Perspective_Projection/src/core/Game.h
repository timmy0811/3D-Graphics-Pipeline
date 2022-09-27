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
		std::string m_windowTitle = "Window";
		bool m_drawAll_;

		// Window
		sf::RenderWindow* m_Window;
		sf::Event ev;
		sf::VideoMode m_VideoMode;

		float dt_;
		float m_movementCamera;

		sf::Clock m_Clock;

		// Game objects
		Pipeline* m_Pipeline;
		Camera* m_Camera;

		ObjectHandler* m_ObjectHandler;

		GUI* m_GUI;

		// Temporary objects
		WavefrontObj* obj = new WavefrontObj();

		// Private functions
		void initVariables();
		void initWindow();
		void initGameObjects() const;
		void initPipeline();

		void updateGameObjects() const;
		void updateGUI() const;

		void setTitle() const;

	public:
		// Constructors
		Game();
		virtual ~Game();

		// Accessors
		const bool getWindowIsOpen() const;

		// Functions
		void pollEvents();
		void update();
		void render() const;
	};
}


