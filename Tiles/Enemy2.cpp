#include "Enemy2.h"

#include <fstream>

Enemy2::Enemy2(Scene& scene)
    : IGameObject(scene)
{
}

void Enemy2::saveAttributes(std::ofstream& file)
{
    file << " PV " << this->PV
         << " age " << this->age;
}

void Enemy2::loadAttributes(const AttributesDict& attributes)
{
    auto it = attributes.find("PV");
    PV = stoi(it->second);
    auto it2 = attributes.find("age");
    age = stoi(it2->second);
}

DEFINE_GAME_OBJECT(Enemy2)
