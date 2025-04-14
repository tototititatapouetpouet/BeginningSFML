#include "Enemy2.h"

#include <fstream>

Enemy2::Enemy2(Scene& scene)
    : IGameObject(scene)
{
}

std::vector<IAttribute*> Enemy2::getAllAttributes()
{
    return { &PV, &age };
}

DEFINE_GAME_OBJECT(Enemy2)
