#include "Game.h"

// Constructors
Game::Game() 
{
    this->initVariables();
    this->initWindow();
    this->initObjects();
}

// Destructors
Game::~Game() {
    delete this->window;
    delete pl;
}

// Private functions

// Init game important variables
void Game::initVariables() {
    this->window = nullptr;
}

// Init game window
void Game::initWindow() {
    this->videoMode.height = 800;
    this->videoMode.width = 800;

    this->window = new sf::RenderWindow(this->videoMode, this->windowTitle, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

void Game::initObjects()
{
    pl = new Pipeline(DISTANCE);

    cubes.push_back(new Cube(sf::Vector3f(0.2f, -1.f, 0.f), 0.5f, sf::Color::White, false));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);

    /*cubes.push_back(new Cube(sf::Vector3f(0.2f, -0.5f, 0.f), 0.5f));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);

    cubes.push_back(new Cube(sf::Vector3f(0.2f, -0.f, 0.f), 0.5f));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);

    cubes.push_back(new Cube(sf::Vector3f(0.2f, 0.5f, 0.f), 0.5f));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);*/

    //polys.push_back(new Triangle(sf::Vector3f(-0.3f, 0.5f, 0.f), sf::Vector3f(0.3f, 0.5f, 0.f), sf::Vector3f(0.0f, -0.5f, 0.f), sf::Color::Magenta));
    //pl->addObjectToQueue(polys[polys.size() - 1]);
}

void Game::setTitle()
{
    float fps = 1.f / this->dt;

    this->window->setTitle(windowTitle + " " + std::to_string(static_cast<int>(fps)));
}

// Accessors

// Check if game is still running
const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

// Functions

// Check for events
void Game::pollEvents() {
    // Event polling
    while (this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->window->close();
            break;
        }
    }
}

// main update method
void Game::update() {
    this->dt = clock.restart().asSeconds();
    this->setTitle();

    this->pollEvents();

    //cubes[0]->rotateX(0.01f);
    /*cubes[0]->rotateY(0.01f);

    cubes[1]->rotateY(0.02f);

    cubes[2]->rotateY(0.03f);

    cubes[3]->rotateY(0.04f);*/

    /*polys[0]->rotateY(0.02f);
    polys[0]->rotateZ(0.03f);*/
}

// main render method
void  Game::render() {
    /*
        Renders game objects to screen
    */

    this->window->clear(sf::Color(0, 0, 0, 255));

    pl->renderAll(window);

    this->window->display();
}