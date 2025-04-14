#pragma once
#include "IGameObject.h"

struct Enemy : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy(Scene& scene);

    void saveAttributes(std::ofstream& file) override;
    void loadAttributes(const AttributesDict& attributes) override;

    int PV = 1;
    Vec2f position;
};
