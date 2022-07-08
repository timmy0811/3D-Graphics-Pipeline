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
}

// Init game important variables
void Game::initVariables() {
    this->window = nullptr;

    drawAll_ = false;
}

// Init game window
void Game::initWindow() {
    this->videoMode.height = c_winHeight;
    this->videoMode.width = c_winWidth;

    this->window = new sf::RenderWindow(this->videoMode, this->windowTitle, sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(c_framerate);

    // ImGui window init
    ImGui::SFML::Init(*window);
}

// Init game objects - soon obsolete
void Game::initGameObjects()
{
    cubes.push_back(new Cube(sf::Vector3f(-0.1f, -0.6f, -0.15f), 0.4f, sf::Color::White, window, false));
    pl->addObjectToQueue(cubes[cubes.size() - 1]);
}

// Init render pipeline
void Game::initPipeline()
{
    // Pipeline setup
    pl = new Pipeline(c_viewPortDistance);
    camera = new Camera();
    pl->setCamera(camera);
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

    // Movement on Y axes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera->move(sf::Vector3f(0.f, 0.05f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera->move(sf::Vector3f(0.0f, -0.05f, 0.f));
    }

    // Camera rotation - WIP
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


void Game::updateGameObjects()
{
    cubes[0]->rotateX(0.015f);
    cubes[0]->rotateY(0.015f);
}

// main update method
void Game::update() {
    // ImGui update
    sf::Time delta = clock.restart();
    ImGui::SFML::Update(*window, delta);

    ImGui::Begin("Object Browser");
    ImGui::Text("Enable Camera Render: ");
    ImGui::Checkbox("Circle", &drawAll_);
    ImGui::End();

    this->dt_ = delta.asSeconds();

    setTitle();
    pollEvents();

    updateGameObjects();
}

// main render method
void  Game::render() {

    this->window->clear(sf::Color(0, 0, 0, 255));

    // Main window render
    if(drawAll_) pl->renderAll(window);

    ImGui::SFML::Render(*window);

    this->window->display();
}