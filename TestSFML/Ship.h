#pragma once

#include "IGameObject.h"

#include <SFML/Graphics.hpp>

class Ship : public IGameObject
{
public:
    Ship();

    void handleInputs() override;
    void update() override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Texture m_texture;
    sf::Sprite m_sprite;

    float m_angle;
    sf::Vector2f m_position;
};
