#include "Game.h"

#include "IGameObject.h"
#include "Ship.h"
#include "Enemy.h"
#include "Barrier.h"

void Game::onCollision(IGameObject* go1, IGameObject* go2)
{
    if (go1->gameObjectType() == SHIP_TYPE && go2->gameObjectType() == ENEMY_TYPE)
    {
        static_cast<Ship*>(go1)->takeDamage();
        go2->destroy();
    }

    if (go1->gameObjectType() == ENEMY_TYPE && go2->gameObjectType() == SHIP_TYPE)
    {
        static_cast<Ship*>(go2)->takeDamage();
        go1->destroy();
    }

    if (go1->gameObjectType() == SHIP_TYPE && go2->gameObjectType() == FIREBALL_TYPE)
    {
        static_cast<Ship*>(go1)->takeDamage(2);
        go2->destroy();
    }

    if (go1->gameObjectType() == FIREBALL_TYPE && go2->gameObjectType() == SHIP_TYPE)
    {
        static_cast<Ship*>(go2)->takeDamage(1);
        go1->destroy();
    }

    if (go1->gameObjectType() == BARRIER_TYPE && go2->gameObjectType() == FIREBALL_TYPE)
    {
        go2->destroy();
    }

    if (go1->gameObjectType() == FIREBALL_TYPE && go2->gameObjectType() == BARRIER_TYPE)
    {
        go1->destroy();
    }
}
