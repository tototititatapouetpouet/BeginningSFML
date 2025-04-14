#pragma once
#include "IGameObject.h"

struct Player : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Player(Scene& scene);

    void saveAttributes(std::ofstream& file) override;
    void loadAttributes(const AttributesDict& attributes) override;

public:
    std::string name = "toto";
    int PV = 3;
    int strenght = 0;
    int dexterity = 0;
    Vec2f position;
};
