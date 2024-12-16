#include "Barrier.h"

Barrier::Barrier(Game& game, const AABB& bbox) : IGameObject(game), m_bbox(bbox)
{ }

void Barrier::handleInputs()
{ }

void Barrier::render(sf::RenderWindow& window)
{}

void Barrier::update()
{
}

AABB Barrier::getBoundingBox() const
{
    return m_bbox;
}

GameObjectType Barrier::gameObjectType()
{
    return BARRIER_TYPE;
}
