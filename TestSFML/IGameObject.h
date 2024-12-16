#pragma once

#include "MyMath.h"

namespace sf { class RenderWindow; }

class Game;

enum GameObjectType
{
    SHIP_TYPE = 0
  , ENEMY_TYPE = 1
  , FIREBALL_TYPE = 2
  , BARRIER_TYPE = 3
};

class IGameObject
{
public:
    IGameObject(Game& g);
    virtual ~IGameObject();

    virtual void handleInputs() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual AABB getBoundingBox() const = 0;
    virtual GameObjectType gameObjectType() = 0;
    void destroy();

protected:
    Game& m_game;
};
