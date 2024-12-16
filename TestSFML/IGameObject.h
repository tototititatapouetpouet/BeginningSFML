#pragma once

#include "MyMath.h"

namespace sf { class RenderWindow; }
namespace sf { class Event; }

class Game;

enum GameObjectType
{
    SHIP_TYPE = 0
  , ENEMY_TYPE = 1
  , FIREBALL_TYPE = 2
  , BARRIER_TYPE = 3
  , PLAYERSHIP_TYPE = 4
};

class IGameObject
{
public:
    IGameObject(Game& g);
    virtual ~IGameObject();

    virtual void handleInputs(const sf::Event& event) = 0;
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual GameObjectType gameObjectType() = 0;
    void destroy();

protected:
    Game& m_game;
};
