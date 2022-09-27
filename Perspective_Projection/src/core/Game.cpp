#include "Game.h"

// Constructors
projection::Game::Game()
{
    initVariables();
    initWindow();
    initPipeline();

    initGameObjects();

}

// Destructors
projection::Game::~Game() {
    // ImGui shutdown
    ImGui::SFML::Shutdown();

    // Game objects
    delete m_Window;
    delete m_Pipeline;
    delete m_Camera;
    delete m_ObjectHandler;
}

// Init game important variables
void projection::Game::initVariables() {
    this->m_Window = nullptr;

    m_drawAll_ = true;
}

// Init game window
void projection::Game::initWindow() {
    // Main window setup
    this->m_VideoMode.height = c_winHeight;
    this->m_VideoMode.width = c_winWidth;

    this->m_Window = new sf::RenderWindow(this->m_VideoMode, this->m_windowTitle, sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(24, 8, 8));
    //this->window->setFramerateLimit(c_framerate);

    // ImGui window init
    ImGui::SFML::Init(*m_Window);
}

// Init render pipeline
void projection::Game::initPipeline()
{
    // Pipeline setup
    m_Pipeline = new Pipeline();
    m_Camera = new Camera();
    m_Pipeline->setCamera(m_Camera);

    m_ObjectHandler = new ObjectHandler(m_Pipeline, m_Camera, m_Window);
    m_GUI = new GUI(m_ObjectHandler);
}

// Update window title
void projection::Game::setTitle() const
{
    // Title shows the current framerate
    this->m_Window->setTitle(m_windowTitle + " " + std::to_string(static_cast<int>(1.f / this->dt_)));
}

// Check if game is still running
const bool projection::Game::getWindowIsOpen() const {
    return this->m_Window->isOpen();
}

// Check for events
void projection::Game::pollEvents() {
    // Event polling
    while (this->m_Window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
        case sf::Event::Closed:
            this->m_Window->close();
            break;
        case sf::Event::KeyPressed:
            if (this->ev.key.code == sf::Keyboard::Escape)
                this->m_Window->close();
            break;
        }

        ImGui::SFML::ProcessEvent(ev);
    }

    // Movement on XZ plane
    m_movementCamera = 2.f;
    m_movementCamera *= dt_;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_Camera->move(sf::Vector3f(0.f, 0.f, m_movementCamera));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_Camera->move(sf::Vector3f(0.f, 0.f, -m_movementCamera));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_Camera->move(sf::Vector3f(m_movementCamera, 0.f, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_Camera->move(sf::Vector3f(-m_movementCamera, 0.0f, 0.f));
    }

    // Movement on Y axes
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_Camera->move(sf::Vector3f(0.f, m_movementCamera, 0.f));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_Camera->move(sf::Vector3f(0.0f, -m_movementCamera, 0.f));
    }

    // Camera rotation - WIP
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_Camera->rotate(sf::Vector2f(0.01f, 0.f), m_ObjectHandler->getRenderObjects());
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_Camera->rotate(sf::Vector2f(-0.01f, 0.f), m_ObjectHandler->getRenderObjects());
    }
    /*if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        camera->rotate(sf::Vector2f(0.f, -movementCamera_));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        camera->rotate(sf::Vector2f(0.f, movementCamera_));
    }*/
}

// Init game objects - soon obsolete
void projection::Game::initGameObjects() const
{
    m_ObjectHandler->createTexture(TexType::BRICKS);

    /*for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            objHandler->createCube(nullptr, sf::Vector3f(i * 0.3f, j * 0.3f, 0.f));
        }
    }*/

    obj->loadFromFile((char*)"Assets/obj/monkey.obj");
    obj->setGlobalOffset(m_Camera->getOffset());

    //objHandler->createCube(nullptr);
    //objHandler->createPlane(nullptr);

    //objHandler->createCube(nullptr);
    //objHandler->createPoint();

    //objHandler->createPoint();

    //objHandler->createPoly(nullptr);
}

void projection::Game::updateGameObjects() const
{/*
    cubes[0]->rotateX(0.015f);
    cubes[0]->rotateY(0.015f);*/
    //objHandler->test_rotate(dt_);
}

void projection::Game::updateGUI() const
{
    m_GUI->menuBar();
    m_GUI->objectBrowser();
    m_GUI->objectAttributes();
    m_GUI->diagnosticsWindow(m_Camera->getOffset(), static_cast<int>(1.f / this->dt_));
}

// main update method
void projection::Game::update() {
    // ImGui update
    sf::Time delta = m_Clock.restart();
    ImGui::SFML::Update(*m_Window, delta);

    this->dt_ = delta.asSeconds();

    setTitle();
    pollEvents();

    updateGameObjects();
    updateGUI();
}

// main render method
void projection::Game::render() const {

    this->m_Window->clear(sf::Color(0, 0, 0, 255));
    //this->window->draw(sf::RectangleShape({ (float)this->window->getSize().x - 500.f, (float)this->window->getSize().y - 500.f }));

    obj->applyPerspective();
    obj->render(m_Window);
    // Draw queue
    if (m_drawAll_) m_Pipeline->renderAll(m_Window);

    // Render GUI frontend
    ImGui::SFML::Render(*m_Window);

    this->m_Window->display();
}

