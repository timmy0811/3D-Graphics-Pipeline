#pragma once

// Frontend
#include "GUI.h"
#include <corecrt_memory.h>

// SFML Graphics Framework
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>

// Engine Components
#include "Point.h"
#include "Cube.h"
#include "Pipeline.h"
#include "Triangle.h"
#include "Camera.h"

#include "ObjectHandler.h"

// Config file
#include "config.h"

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

