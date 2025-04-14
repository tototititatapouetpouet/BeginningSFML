#pragma once
#include "IGameObject.h"

struct Enemy2 : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy2(Scene& scene);

    std::vector<IAttribute*> getAllAttributes() override;

    Attribute<int> PV = { "PV", 2 };
    Attribute<int> age = { "age", 12 };

    Vec2f position;
};
