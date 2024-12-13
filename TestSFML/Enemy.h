#pragma once

#pragma once

#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class Game;

class Enemy : public IGameObject
{
public:
    Enemy(Game& game, const Vec2& position, const Vec2& velocity);

    void handleInputs() override;
    void update() override;
    void render(sf::RenderWindow& window) override;
    AABB getBoundingBox() const override;
    GameObjectType gameObjectType() override;

private:
    sf::Sprite m_sprite;

    Vec2 m_position;
    Vec2 m_velocity;
};

