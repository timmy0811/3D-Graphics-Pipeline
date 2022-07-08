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
    delete camera;
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
    camera = new Camera();
    pl->setCamera(camera);

    cubes.push_back(new Cube(sf::Vector3f(-0.1f, -0.15f, -0.15f), 0.5f, sf::Color::White, window, false));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        camera->move(sf::Vector3f(0.f, 0.f, -0.05f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        camera->move(sf::Vector3f(0.f, 0.f, 0.05f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        camera->move(sf::Vector3f(0.05f, 0.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        camera->move(sf::Vector3f(-0.05f, 0.0f, 0.f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera->move(sf::Vector3f(0.f, 0.05f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera->move(sf::Vector3f(0.0f, -0.05f, 0.f));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        camera->rotate(sf::Vector2f(0.05f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        camera->rotate(sf::Vector2f(-0.05f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        camera->rotate(sf::Vector2f(0.f, -0.05f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        camera->rotate(sf::Vector2f(0.f, 0.05f));
    }
}

// main update method
void Game::update() {
    this->dt = clock.restart().asSeconds();
    this->setTitle();

    this->pollEvents();

    cubes[0]->rotateX(0.015f);
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