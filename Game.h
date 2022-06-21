#pragma once

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

	// Window
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;

	sf::Clock clock;

	// Private functions
	void initVariables();
	void initWindow();

	void setTitle();

	// Game Logic
	float dt;

	// Game objects
	std::vector<Point*> point;

	

	float z0;

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
	void renderPoints();

	void projectObjects();
	void rotateObjects();
};

