#pragma once
#include "IGameObject.h"

struct Enemy2 : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Enemy2(Scene& scene);
};
