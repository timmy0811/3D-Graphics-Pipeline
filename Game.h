#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

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

