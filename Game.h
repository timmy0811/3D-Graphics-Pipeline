#pragma once

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include <vector>

#include "Matrix.h"
#include "Matrix3X1.h"
#include "Matrix3X3.h"
#include "MatrixOperations.h"

#include "Point.h"
#include "Cube.h"
#include "Pipeline.h"
#include "Triangle.h"
#include "Camera.h"

#define DISTANCE 2.f
#define FOV 80.f

#define M_PI 3.14159265f

/*
	Game depending functions
*/

class Game
{
private:
	// Variables
	std::string windowTitle = "Window";
	bool drawAll;

	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	sf::Clock clock;

	// Private functions
	void initVariables();
	void initWindow();
	void initObjects();

	void setTitle();

	// Game Logic
	float dt;

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

