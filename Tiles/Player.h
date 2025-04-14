#pragma once
#include "IGameObject.h"

struct Player : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Player(Scene& scene);

    void saveAttributes(std::ofstream& file) override;
    void loadAttributes(const AttributesDict& attributes) override;

public:
    Attribute<std::string> name = { "name", "toto" };
    Attribute<int> PV = { "PV", 3 };
    Attribute<int> strenght = { "strenght", 0 };
    Attribute<int> dexterity = { "dexterity", 0 };
    Vec2f position;
};
