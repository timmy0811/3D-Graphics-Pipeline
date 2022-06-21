#include "Game.h"

// Constructors
Game::Game() {
    this->initVariables();
    this->initWindow();
}

// Destructors
Game::~Game() {
    delete this->window;

    for (Point* p : this->point) {
        delete p;
    }
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

    z0 = (window->getSize().x / 2.f) / tan((FOV / 2.f) * M_PI / 180.f);
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

    this->rotateObjects();
    //this->projectObjects();
}

// main render method
void  Game::render() {
    /*
        Renders game objects to screen
    */

    this->window->clear(sf::Color(0, 0, 0, 255));

    this->renderPoints();
    Point::connect(window, point);

    this->window->display();
}

void Game::renderPoints()
{
    for (Point* p : this->point) {
        p->render(this->window);
    }
}

void Game::projectObjects()
{
    for (Point* p : this->point) {
        /*(*(p->getProjMatrix())).x0 = (*(p->getMatrix())).x0 * z0 / (z0 + (*(p->getMatrix())).z0);
        (*(p->getProjMatrix())).y0 = (*(p->getMatrix())).y0 * z0 / (z0 + (*(p->getMatrix())).z0);
        (*(p->getProjMatrix())).z0 = (*(p->getMatrix())).z0;*/

        (*(p->getProjMatrix())).x0 = (*(p->getMatrix())).x0 / (DISTANCE - (*(p->getMatrix())).z0);
        (*(p->getProjMatrix())).y0 = (*(p->getMatrix())).y0 / (DISTANCE - (*(p->getMatrix())).z0);
        (*(p->getProjMatrix())).z0 = (*(p->getMatrix())).z0;
    }
}

void Game::rotateObjects()
{
    for (Point* p : this->point) {
        // Rotate
        *(p->getMatrix()) = maop::matMul(this->rotationY, *(p->getMatrix()));
        *(p->getMatrix()) = maop::matMul(this->rotationX, *(p->getMatrix()));
        *(p->getMatrix()) = maop::matMul(this->rotationZ, *(p->getMatrix()));

        /*projection.x0 = 1.f;
        projection.y1 = 1.f;
        projection.z2 = 1.f;*/

        // Project
        //*(p->getMatrix()) = maop::matMul(projection, *(p->getMatrix()));
        projectObjects();
    }
}

