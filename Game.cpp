#include "Game.h"

// Constructors
Game::Game() 
{
    initVariables();
    initWindow();
    initPipeline();

    initGameObjects();
}

// Destructors
Game::~Game() {
    // ImGui shutdown
    ImGui::SFML::Shutdown();

    // Game objects
    delete window;
    delete pl;
    delete camera;
    delete objHandler;
}

// Init game important variables
void Game::initVariables() {
    this->window = nullptr;

    drawAll_ = true;
}

// Init game window
void Game::initWindow() {
    // Main window setup
    this->videoMode.height = c_winHeight;
    this->videoMode.width = c_winWidth;

    this->window = new sf::RenderWindow(this->videoMode, this->windowTitle, sf::Style::Titlebar | sf::Style::Close);
    //this->window->setFramerateLimit(c_framerate);

    // ImGui window init
    ImGui::SFML::Init(*window);
}

// Init render pipeline
void Game::initPipeline()
{
    // Pipeline setup
    pl = new Pipeline(c_viewPortDistance);
    camera = new Camera();
    pl->setCamera(camera);

    objHandler = new ObjectHandler(pl, camera, window);
}

// Update window title
void Game::setTitle()
{
    // Title shows the current framerate
    this->window->setTitle(windowTitle + " " + std::to_string(static_cast<int>(1.f / this->dt_)));
}

// Check if game is still running
const bool Game::getWindowIsOpen() const {
    return this->window->isOpen();
}

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

        ImGui::SFML::ProcessEvent(ev);
    }

    // Movement on XZ plane
    movementCamera_ = 2.f;
    movementCamera_ *= dt_;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        camera->move(sf::Vector3f(0.f, 0.f, movementCamera_));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        camera->move(sf::Vector3f(0.f, 0.f, -movementCamera_));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        camera->move(sf::Vector3f(movementCamera_, 0.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        camera->move(sf::Vector3f(-movementCamera_, 0.0f, 0.f));
    }

    // Movement on Y axes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        camera->move(sf::Vector3f(0.f, movementCamera_, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        camera->move(sf::Vector3f(0.0f, -movementCamera_, 0.f));
    }

    // Camera rotation - WIP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        camera->rotate(sf::Vector2f(movementCamera_, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        camera->rotate(sf::Vector2f(-movementCamera_, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera->rotate(sf::Vector2f(0.f, -movementCamera_));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera->rotate(sf::Vector2f(0.f, movementCamera_));
    }
}

// Init game objects - soon obsolete
void Game::initGameObjects()
{
    /*for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            objHandler->createCube(sf::Vector3f(i * 0.3f, j * 0.3f, 0.f));
        }
    }*/
    objHandler->createTexture(TexType::BRICKS);
    objHandler->createCube(nullptr, sf::Vector3f(0.f, 0.f, 1.f));
    //objHandler->createPoint();

    //objHandler->createPoint();

    //objHandler->createPoly();
}

void Game::updateGameObjects()
{/*
    cubes[0]->rotateX(0.015f);
    cubes[0]->rotateY(0.015f);*/
    objHandler->test_rotate(dt_);
}

void Game::updateGUI()
{
    GUI::menuBar();
    GUI::objectBrowser(objHandler->getObjects());
    GUI::objectAttributes(objHandler->getActiveObj());
    GUI::diagnosticsWindow(camera->getOffset(), static_cast<int>(1.f / this->dt_));
}

// main update method
void Game::update() {
    // ImGui update
    sf::Time delta = clock.restart();
    ImGui::SFML::Update(*window, delta);

    this->dt_ = delta.asSeconds();

    setTitle();
    pollEvents();

    updateGameObjects();
    updateGUI();
}

// main render method
void Game::render() {

    this->window->clear(sf::Color(0, 0, 0, 255));

    // Draw queue
    if (drawAll_) pl->renderAll(window);

    // Render GUI frontend
    ImGui::SFML::Render(*window);

    /*for (register int i = 0; i < c_winHeight * c_winWidth; i += 4) {
        buffer[i] = 0 % 255;
        buffer[i + 1] = ( 100) % 255;
        buffer[i + 2] = ( 200) % 255;
        buffer[i + 3] = 255;
    }*/

    this->window->display();
}

