#pragma once

// ImGui Frontend
#include "imgui.h"
#include "imgui-SFML.h"

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

	sf::Clock clock;

	// Private functions
	void initVariables();
	void initWindow();
	void initGameObjects();
	void initPipeline();

	void updateGameObjects();

	void setTitle();

	// Game objects
	Pipeline* pl;
	Camera* camera;

	std::vector<Cube*> cubes;
	std::vector<Point*> points;
	std::vector<Triangle*> polys;

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

