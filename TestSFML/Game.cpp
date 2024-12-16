#include "Game.h"

//  TODO: To be removed!!!!!!!
#include <iostream>

#include <array>

#include "IGameObject.h"
#include "Ship.h"
#include "PlayerShip.h"
#include "Enemy.h"
#include "Barrier.h"

constexpr int getWindowWidth() { return 1900; }
constexpr int getWindowHeight() { return 1000; }

Game::Game() : m_window(sf::VideoMode(getWindowWidth(), getWindowHeight()), "SFML works!")
{
    m_window.setFramerateLimit(60);

    new Barrier(*this, { { -20.f, -20.f }, { getWindowWidth() + 20.f, 10.f } });
    new Barrier(*this, { { -20.f, getWindowHeight() - 10.f }, { getWindowWidth() + 20.f, getWindowHeight() + 20.f } });
    new Barrier(*this, { { -20.f, -20.f }, { 10.f, getWindowHeight() + 20.f } });
    new Barrier(*this, { { getWindowWidth() - 10.f, -20.f }, { getWindowWidth() + 20.f, getWindowHeight() + 20.f } });

    /*
    new Ship(*this, { 300.f, 300.f });
    new Ship(*this, { 400.f, 400.f });
    new Enemy(*this, { 0.f, 300.f }, { 40.f, 0.f });
    new Enemy(*this, { -80.f, 300.f }, { 40.f, 0.f });
    */

    new PlayerShip(*this, { 300.0f, 300.f });
}

Game::~Game()
{
    auto allGameObjects = m_allGameObjects;
    for (auto& gameObject : allGameObjects)
        delete gameObject;
}

void Game::_addObject(IGameObject* go)
{
    m_toBeAddedGameObjects.push_back(go);
}

struct RemoveNonExisitingGameObject : public std::runtime_error
{
    RemoveNonExisitingGameObject() : std::runtime_error("Try to remove non existing Game Object.")
    { }
};

void Game::_removeObject(IGameObject* go)
{
    auto it = std::find(m_allGameObjects.begin(), m_allGameObjects.end(), go);
    if (it == m_allGameObjects.end()) // No elem found.
        throw RemoveNonExisitingGameObject();

    m_allGameObjects.erase(it);
}

void Game::_toBeRemoveObject(IGameObject* go)
{
    auto it = std::find(m_toBeRemovedGameObjects.begin(), m_toBeRemovedGameObjects.end(), go);

    if (it != m_toBeRemovedGameObjects.end())
        return;

    m_toBeRemovedGameObjects.push_back(go);
}

void Game::_cleanObject()
{
    for (auto& go : m_toBeRemovedGameObjects)
        delete go;

    m_toBeRemovedGameObjects.clear();
}

void Game::_deferedAddObject(IGameObject* go)
{
    m_allGameObjects.push_back(go);
}

void Game::_deferedAddObjects()
{
    for (auto& go : m_toBeAddedGameObjects)
        _deferedAddObject(go);

    m_toBeAddedGameObjects.clear();
}

void Game::update()
{
    _deferedAddObjects();

    detectCollision();
    for (auto& gameObject : m_allGameObjects)
        gameObject->update(1.f / 60.f); //  TODO: fous ça ailleurs !!!

    _cleanObject();
}

void Game::detectCollision()
{
    for (size_t i = 0; i < m_allGameObjects.size(); ++i)
    {
        for (size_t j = i + 1; j < m_allGameObjects.size(); ++j)
        {
            IGameObject* go1 = m_allGameObjects[i];
            IGameObject* go2 = m_allGameObjects[j];
            
            bool isIntersection = doesIntersect(go1->getBoundingBox(), go2->getBoundingBox());
            if (isIntersection)
                onCollision(go1, go2);
        }
    }
}

void Game::render()
{
    m_window.clear();

    for (auto& gameObject : m_allGameObjects)
        gameObject->render(m_window);

    renderBoundingBox();

    m_window.display();
}

void Game::renderBoundingBox()
{
    for (const auto& go : m_allGameObjects)
    {
        AABB bbox = go->getBoundingBox();
        sf::Color col = sf::Color::Green;
        std::array<sf::Vertex, 8> lines = {
            sf::Vertex{{bbox.min.x, bbox.min.y}, col}, sf::Vertex{{bbox.max.x, bbox.min.y}, col}
          , sf::Vertex{{bbox.max.x, bbox.min.y}, col}, sf::Vertex{{bbox.max.x, bbox.max.y}, col}
          , sf::Vertex{{bbox.max.x, bbox.max.y}, col}, sf::Vertex{{bbox.min.x, bbox.max.y}, col}
          , sf::Vertex{{bbox.min.x, bbox.max.y}, col}, sf::Vertex{{bbox.min.x, bbox.min.y}, col}
        };

        m_window.draw(&lines[0], lines.size(), sf::Lines);
    }
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

    for (auto& go : m_allGameObjects)
        go->handleInputs(event);
}

TextureCache& Game::getTextureCache()
{
    return m_textureCache;
}
