#pragma once
#include "IGameObject.h"

struct Enemy : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy(Scene& scene);

    std::vector<IAttribute*> getAllAttributes() override;

    Attribute<int> PV = { "PV", 1 };

    Vec2f position;
};
