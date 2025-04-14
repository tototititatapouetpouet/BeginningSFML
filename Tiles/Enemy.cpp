#include "Enemy.h"

#include <fstream>

Enemy::Enemy(Scene& scene)
    : IGameObject(scene)
{
}

std::vector<IAttribute*> Enemy::getAllAttributes()
{
    return { &PV };
}

DEFINE_GAME_OBJECT(Enemy)
