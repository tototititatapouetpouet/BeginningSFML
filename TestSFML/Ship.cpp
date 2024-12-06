#include "Ship.h"

Ship::Ship() : m_angle(0.f), m_position(300.0f, 300.0f)
{
    m_texture.loadFromFile("C:\\repoGC\\BeginningSFML\\Truc.bmp");
    m_sprite.setTexture(m_texture);
}

void Ship::handleInputs()
{

}

void Ship::update()
{
    m_angle += 0.01f;
}

void Ship::render(sf::RenderWindow& window)
{
    m_sprite.setRotation(m_angle / 3.14159265f * 180.f);
    m_sprite.setOrigin(128.f / 2.f, 128.f / 2.f);
    m_sprite.setPosition(m_position);
    window.draw(m_sprite);
}
