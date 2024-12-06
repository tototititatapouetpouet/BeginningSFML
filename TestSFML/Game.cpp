#include "Game.h"

#include "IGameObject.h"
#include "Ship.h"

Game::Game() : m_window(sf::VideoMode(600, 600), "SFML works!")
{
    m_window.setFramerateLimit(60);

    for (int i = 0; i < 10000; ++i)
    {
        Ship* ship = new Ship();
        m_allGameObjects.push_back(ship);
    }
}

Game::~Game()
{
    for (auto& gameObject : m_allGameObjects)
        delete gameObject;
}

void Game::update()
{
    for (auto& gameObject : m_allGameObjects)
        gameObject->update();
}

void Game::render()
{
    m_window.clear();

    for (auto& gameObject : m_allGameObjects)
        gameObject->render(m_window);

    m_window.display();
}

void Game::run()
{
    while (m_window.isOpen())
    {
        handleInputs();
        update();
        render();
    }
}

void Game::handleInputs()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            m_window.close();
    }
}
