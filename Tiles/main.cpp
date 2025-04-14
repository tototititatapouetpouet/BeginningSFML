#include <SFML/Graphics.hpp>

#include "IGameObject.h"

#include "Scene.h"

#include <fstream>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    Scene scene("Level2.txt");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                scene.click(event.mouseButton.x, event.mouseButton.y);
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    scene.getView().targetY -= 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    scene.getView().targetY += 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    scene.getView().targetX -= 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    scene.getView().targetX += 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {
                    scene.getView().scale *= 1.1f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    scene.getView().scale /= 1.1f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
                {
                    scene.m_selectedTileIdx++;
                    scene.m_selectedTileIdx %= 3; //    TODO : le 3 ca serait bien de savoir d'ou ca vient.
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                {
                    scene.m_selectedTileIdx--;
                    if (scene.m_selectedTileIdx == -1)
                        scene.m_selectedTileIdx = (3 - 1);//    TODO : le 3 ca serait bien de savoir d'ou ca vient.
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                {
                    scene.save("Level3.txt");
                }
            }
        }

        // Super Duper degeux !!!
        scene.getView().update();

        window.clear();
        scene.render(window);
        window.display();
    }

    return 0;
}