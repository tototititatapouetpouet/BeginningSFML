#include "Enemy.h"

#include <fstream>

Enemy::Enemy(Scene& scene)
    : IGameObject(scene)
{
}

void Enemy::saveAttributes(std::ofstream& file)
{
    file << " PV " << this->PV;
}

void Enemy::loadAttributes(const AttributesDict& attributes)
{
    auto it = attributes.find("PV");
    PV = stoi(it->second);
}

DEFINE_GAME_OBJECT(Enemy)
