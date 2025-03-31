#pragma once
#include "IGameObject.h"

struct Enemy : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy(Scene& scene);
};
