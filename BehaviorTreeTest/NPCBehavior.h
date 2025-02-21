#pragma once

#include "Tree.h"
#include "NPC.h"

namespace BT
{
    class IfGunEmpty : public IConditionalNode
    {
    public:
        IfGunEmpty(ICompositeNode* node)
            : IConditionalNode(node)
        {
        }

        bool condition()
        {
            return getNpc()->isClipEmpty();
        }
    };

    class ReloadGun : public IActionNode
    {
    public:
        ReloadGun(ICompositeNode* parent) : IActionNode(parent)
        {
        }

        Status tick() override
        {
            getNpc()->reloadGun();
            m_delay--;
            if (m_delay >= 1)
            {
                std::cout << "Gun reloading .";
                return Running;
            }

            std::cout << ". DONE!" << std::endl;
            m_delay = 2;
            return Success;
        }

    private:
        int m_delay = 2;
    };

    class Fire : public IActionNode
    {
    public:
        Fire(ICompositeNode* parent) : IActionNode(parent)
        {
        }

        Status tick() override
        {
            if (!getNpc()->isCurrentTargetValid())
                return Failed;

            if (getNpc()->fire())
                return Success;

            return Failed;
        }
    };

    class IsEnemyDead : public IActionNode
    {
    public:
        IsEnemyDead(ICompositeNode* parent) : IActionNode(parent)
        {
        }

        Status tick() override
        {
            if (getNpc()->getCurrentTarget()->PV <= 0)
            {
                std::cout << "Enemy killed!" << std::endl;
                return Success;
            }

            return Failed;
        }
    };

    class FindEnemy : public IActionNode
    {
    public:
        FindEnemy(ICompositeNode* parent) : IActionNode(parent)
        {
        }

        Status tick() override
        {
            getNpc()->findValidTarget();
            if (getNpc()->getCurrentTarget() == nullptr)
            {
                std::cout << "No enemy left!" << std::endl;
                return Failed;
            }

            std::cout << "Enemy spotted!" << std::endl;
            return Success;
        }
    };

    class VictoryDance : public IActionNode
    {
    public:
        VictoryDance(ICompositeNode* parent) : IActionNode(parent)
        {
        }

        Status tick() override
        {
            if (m_delay <= 0)
            {
                std::cout << std::endl;
                return Success;
            }
            std::vector<std::string> danceSteps = { "\\o/", "|o/", "\\o|", "-o-" };
            std::cout << danceSteps[m_delay % 4] << " ";
            m_delay--;

            return Running;
        }

    private:
        int m_delay = 12;
    };
}
