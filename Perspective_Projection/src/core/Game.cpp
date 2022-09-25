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

    this->window = new sf::RenderWindow(this->videoMode, this->windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24, 8, 8));
    //this->window->setFramerateLimit(c_framerate);

    // ImGui window init
    ImGui::SFML::Init(*window);
}

// Init render pipeline
void Game::initPipeline()
{
    // Pipeline setup
    pl = new Pipeline();
    camera = new Camera();
    pl->setCamera(camera);

    objHandler = new ObjectHandler(pl, camera, window);
    GUI_ = new GUI(objHandler);
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
        camera->rotate(sf::Vector2f(0.01f, 0.f), objHandler->getRenderObjects());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        camera->rotate(sf::Vector2f(-0.01f, 0.f), objHandler->getRenderObjects());
    }
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera->rotate(sf::Vector2f(0.f, -movementCamera_));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera->rotate(sf::Vector2f(0.f, movementCamera_));
    }*/
}

// Init game objects - soon obsolete
void Game::initGameObjects()
{
    objHandler->createTexture(TexType::BRICKS);

    /*for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objHandler->createCube(nullptr, sf::Vector3f(i * 0.3f, j * 0.3f, 0.f));
        }
    }*/
   
    obj->loadFromFile((char*)"Assets/obj/monkey.obj");
    obj->setGlobalOffset(camera->getOffset());

    //objHandler->createCube(nullptr);
    //objHandler->createPlane(nullptr);

    //objHandler->createCube(nullptr);
    //objHandler->createPoint();

    //objHandler->createPoint();

    //objHandler->createPoly(nullptr);
}

void Game::updateGameObjects()
{/*
    cubes[0]->rotateX(0.015f);
    cubes[0]->rotateY(0.015f);*/
    //objHandler->test_rotate(dt_);
}

void Game::updateGUI()
{
    GUI_->menuBar();
    GUI_->objectBrowser();
    GUI_->objectAttributes();
    GUI_->diagnosticsWindow(camera->getOffset(), static_cast<int>(1.f / this->dt_));
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
    //this->window->draw(sf::RectangleShape({ (float)this->window->getSize().x - 500.f, (float)this->window->getSize().y - 500.f }));

    obj->applyPerspective();
    obj->render(window);
    // Draw queue
    if (drawAll_) pl->renderAll(window);

    // Render GUI frontend
    ImGui::SFML::Render(*window);

    this->window->display();
}

