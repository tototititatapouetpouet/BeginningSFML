#pragma once
#include "IGameObject.h"

struct Enemy2 : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy2(Scene& scene);

    void saveAttributes(std::ofstream& file) override;
    void loadAttributes(const AttributesDict& attributes) override;

    int PV = 2;
    Vec2f position;
    int age = 12;
};
