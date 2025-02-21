#pragma once

#include "Tree.h"

#include <array>
#include <vector>
#include <iostream>

struct Game;

class GameObject
{
};

struct Enemy : public GameObject
{
    int PV = 3;
};

namespace {
    int NPC_MAX_AMMO() { return 5; }
}

class NPC : public GameObject
{
public:
    NPC(Game& game);

    void update();

    void findValidTarget();

    Enemy* getCurrentTarget()
    {
        return m_currentTarget;
    }

    bool isCurrentTargetValid() const
    {
        if (m_currentTarget == nullptr)
            return false;

        if (m_currentTarget->PV <= 0)
            return false;

        return true;
    }

    bool isClipEmpty() const
    {
        return m_ammo <= 0;
    }

    void reloadGun()
    {
        m_ammo = NPC_MAX_AMMO();
    }

    bool fire()
    {
        if (m_ammo <= 0)
        {
            std::cout << "CLIC: Oh Shit!" << std::endl;
            return false;
        }

        std::cout << "BANG : Fire the gun!" << std::endl;

        m_ammo--;

        if (isCurrentTargetValid())
            getCurrentTarget()->PV--;

        return true;
    }

private:
    Enemy* m_currentTarget;
    Game& m_game;
    BT::RootNode m_rootNode;
    int m_ammo;
};

struct Game
{
    Game() : npc(*this)
    {
    }

    void exec();

    NPC npc;
    std::array<Enemy, 5> enemies;
};
