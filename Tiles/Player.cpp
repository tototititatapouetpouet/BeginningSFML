#include "Player.h"

#include <iostream>
#include <array>
#include <fstream>

Player::Player(Scene& scene)
    : IGameObject(scene)
{
}

void Player::saveAttributes(std::ofstream& file)
{
    std::array<IAttribute*, 4> allAttributes = {&name, &PV, &strenght, &dexterity };
    for (auto*& attribute : allAttributes)
        attribute->save(file);
}

void Player::loadAttributes(const AttributesDict& attributeDict)
{
    std::array<IAttribute*, 4> allAttributes = { &name, &PV, &strenght, &dexterity };
    for (auto*& attribute : allAttributes)
    {
        auto it = attributeDict.find(attribute->getName());
        if (it == attributeDict.end())
            continue;

        attribute->load(it->second);
    }
}

// Grace a la macro magique
//bool toto = [](){theGameObjectFactory().registerType<Player>(); return true; }();

// Equivalant a :
// bool tartempion()
// {
//     theGameObjectFactory().registerType<Player>();
//     return true;
// }
// 
// bool toto = tartempion();

DEFINE_GAME_OBJECT(Player)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                     