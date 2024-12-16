#pragma once

#include "IGameObject.h"

class Barrier : public IGameObject
{
public:
    Barrier(Game& game, const AABB& bbox);

    void handleInputs() override;
    void render(sf::RenderWindow& window) override;
    AABB getBoundingBox() const override;
    GameObjectType gameObjectType() override;
    void update() override;

private:
    AABB m_bbox;
};
