#pragma once

#include <SFML/Graphics.hpp>

class IGameObject;

class Game
{
public:
    Game();
    ~Game();

    void handleInputs();

    void update();

    void render();

    void run();

private:
    sf::RenderWindow m_window;
    std::vector<IGameObject*> m_allGameObjects;
};
