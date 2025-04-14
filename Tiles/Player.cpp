#include "Player.h"

#include <iostream>
#include <fstream>

Player::Player(Scene& scene)
    : IGameObject(scene)
{
}

void Player::saveAttributes(std::ofstream& file)
{
    file << " name " << name
         << " PV " << PV
         << " strenght " << strenght
         << " dexterity " << dexterity;
}

void Player::loadAttributes(const AttributesDict& attributes)
{
    auto it_name = attributes.find("name");
    name = it_name->second;

    auto it_PV = attributes.find("PV");
    PV = stoi(it_PV->second);

    auto it_strenght = attributes.find("strenght");
    strenght = stoi(it_strenght->second);

    auto it_dexterity = attributes.find("dexterity");
    dexterity = stoi(it_dexterity->second);
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                     