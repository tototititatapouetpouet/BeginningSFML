#pragma once
#include "IGameObject.h"

struct Player : public IGameObject
{
    DECLARE_GAME_OBJECT()

    Player();
};
