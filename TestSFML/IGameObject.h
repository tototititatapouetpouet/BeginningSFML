#pragma once

namespace sf { class RenderWindow; }

class IGameObject
{
public:
    virtual ~IGameObject() = default;

    virtual void handleInputs() = 0;
    virtual void update() = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};
