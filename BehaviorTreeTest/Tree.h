#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <type_traits>

struct Game;

struct Enemy
{
    int PV = 3;
};

namespace {
    int NPC_MAX_AMMO() { return 5; }
}

struct NPC
{
    NPC(Game& game) : m_game(game), m_currentTarget(nullptr), m_ammo(NPC_MAX_AMMO())
    { }

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

private:
    Enemy* m_currentTarget;
    Game& m_game;
    int m_ammo;
};

struct Game
{
    Game() : npc(*this)
    {}

    NPC npc;
    std::array<Enemy, 5> enemies;
};


namespace BT
{

    class CompositeNode;

    enum Status
    {
        Success
      , Failed
      , Running
    };

    struct IComponentNode
    {
        IComponentNode(CompositeNode* parent = nullptr);

        void setParent(CompositeNode* newParent);

        virtual ~IComponentNode();

        virtual void display() = 0;

        virtual Status tick() = 0;

    protected: 
        CompositeNode* m_parent;
    };

    struct ActionNode : IComponentNode
    {
        ActionNode(CompositeNode* node = nullptr)
            : IComponentNode(node)
        {
        }

        void display() override
        {
            std::cout << "child" << std::endl;
        }
    };

    class CompositeNode : public IComponentNode
    {
    public:
        friend IComponentNode;

        CompositeNode(CompositeNode* node = nullptr)
            : IComponentNode(node)
        {
        }

        ~CompositeNode()
        {
            for(std::make_signed_t<size_t> idx = m_children.size() - 1 ; idx >= 0 ; --idx)
            {
                delete m_children[idx];
                std::cout << "je detruis les trucs qui trainent" << std::endl;
            }
        }

        void display() override
        {
            for (auto& child : m_children)
                child->display();
        }

    protected:
        const std::vector<IComponentNode*>& getChildren() const
        {
            return m_children;
        }

    private:
        void add(IComponentNode* node)
        {
            m_children.push_back(node);
        }

        void remove(IComponentNode* node)
        {
            auto it = std::find(m_children.begin(), m_children.end(), node);
            if (it == m_children.end())
                throw;

            m_children.erase(it);
        }

    private:
        std::vector<IComponentNode*> m_children;

    };
    
    class ControlNode;

    template<Status STATUS>
    class IStrategy
    {
    public:
        virtual ~IStrategy() = default;
        virtual Status execute(ControlNode* node) = 0;
    };

    class ControlNode : public CompositeNode
    {
    public:
        ControlNode(CompositeNode* parent, IStrategy<Failed>* failedStrategy, IStrategy<Running>* runningStrategy, IStrategy<Success>* successStrategy)
            : CompositeNode(parent)
            , m_nextNodeToTick(0)
            , m_failedStrategy(failedStrategy)
            , m_runningStrategy(runningStrategy)
            , m_successStrategy(successStrategy)
        {
        }

        ~ControlNode()
        {
            delete m_failedStrategy;
            delete m_runningStrategy;
            delete m_successStrategy;
        }

        void reset()
        {
            m_nextNodeToTick = 0;
        }

        void incrementChildrenIndex()
        {
            m_nextNodeToTick++;
        }

        bool isLastChildren() const
        {
            return m_nextNodeToTick == getChildren().size() - 1;
        }

        virtual Status tick()
        {
            Status childStatus = getChildren()[m_nextNodeToTick]->tick();

            if (childStatus == Failed)
                return m_failedStrategy->execute(this);

            if (childStatus == Running)
                return m_runningStrategy->execute(this);

            if (childStatus == Success)
                return m_successStrategy->execute(this);

            throw;
        }

    private:
        size_t m_nextNodeToTick;
        IStrategy<Failed>* m_failedStrategy;
        IStrategy<Running>* m_runningStrategy;
        IStrategy<Success>* m_successStrategy;
    };



    struct FailedStrategy : public IStrategy<Failed>
    {
        virtual Status execute(ControlNode* node)
        {
            node->reset();
            return Failed;
        }
    };

    struct RetryStrategy : public IStrategy<Failed>
    {
        virtual Status execute(ControlNode* node)
        {
            node->reset();
            return Running;
        }
    };

    struct RunningStrategy : public IStrategy<Running>
    {
        virtual Status execute(ControlNode* node)
        {
            return Running;
        }
    };

    struct SuccessStrategy : public IStrategy<Success>
    {
        virtual Status execute(ControlNode* node)
        {
            if (node->isLastChildren())
            {
                node->reset();
                return Success;
            }
            
            node->incrementChildrenIndex();
            return Running;
        }
    };

    struct RedoNTimeStrategy : public IStrategy<Success>
    {
        RedoNTimeStrategy(int N) : m_N(N)
        {}

        virtual Status execute(ControlNode* node)
        {
            if (node->isLastChildren())
            {
                node->reset();
                m_N--;
                if (m_N == 0)
                    return Success;

                return Running;
            }

            node->incrementChildrenIndex();
            return Running;
        }

    private:
        int m_N;
    };

    struct RedoStrategy : public IStrategy<Success>
    {
        virtual Status execute(ControlNode* node)
        {
            if (node->isLastChildren())
            {
                node->reset();
                return Running;
            }

            node->incrementChildrenIndex();
            return Running;
        }
    };

    struct FailAsSuccessStrategy : public IStrategy<Failed>
    {
        virtual Status execute(ControlNode* node)
        {
            node->reset();
            return Success;
        }
    };

    class DoNTime : public ControlNode
    {
    public:
        DoNTime(CompositeNode* parent = nullptr, int N = 3) :
            ControlNode(parent, new FailedStrategy, new RunningStrategy, new RedoNTimeStrategy{N})
        {
        }
    };

    class DoUntilFailure : public ControlNode
    {
    public:
        DoUntilFailure(CompositeNode* parent = nullptr) :
            ControlNode(parent, new FailAsSuccessStrategy, new RunningStrategy, new RedoStrategy)
        {
        }
    };

    class Sequence : public ControlNode
    {
    public:
        Sequence(CompositeNode* parent = nullptr) :
            ControlNode(parent, new FailedStrategy, new RunningStrategy, new SuccessStrategy)
        {}
    };

    class Retry : public ControlNode
    {
    public:
        Retry(CompositeNode* parent = nullptr) :
            ControlNode(parent, new RetryStrategy, new RunningStrategy, new SuccessStrategy)
        {
        }
    };

    class IsGunEmpty : public ActionNode
    {
    public:
        IsGunEmpty(CompositeNode* parent, NPC* npc) : ActionNode(parent), m_npc(npc)
        {
        }

        Status tick() override
        {
            if 
        }

    private:
        NPC* m_npc;
    };

    class ReloadGun : public ActionNode
    {
    public:
        ReloadGun(CompositeNode* parent, NPC* npc) : ActionNode(parent), m_npc(npc)
        {
        }

        Status tick() override
        {
            m_npc->reloadGun();
            m_delay--;
            if (m_delay >= 1)
                return Running;
            
            std::cout << "Gun reloaded!" << std::endl;
            return Success;
        }

    private:
        int m_delay = 2;
        NPC* m_npc;
    };

    class Fire : public ActionNode
    {
    public:
        Fire(CompositeNode* parent, NPC* npc) : ActionNode(parent), m_npc(npc)
        {
        }

        Status tick() override
        {
            if (!m_npc->isCurrentTargetValid())
                return Failed;

            std::cout << "Fire the gun!" << std::endl;
            m_npc->getCurrentTarget()->PV--;
            return Success;
        }

    private:
        NPC* m_npc;
    };

    class IsEnemyDead : public ActionNode
    {
    public:
        IsEnemyDead(CompositeNode* parent, NPC* npc) : ActionNode(parent), m_npc(npc)
        {
        }

        Status tick() override
        {
            if (m_npc->getCurrentTarget()->PV <= 0)
            {
                std::cout << "Enemy killed!" << std::endl;
                return Success;
            }
            
            return Failed;
        }

    private:
        NPC* m_npc;
    };

    class FindEnemy : public ActionNode
    {
    public:
        FindEnemy(CompositeNode* parent, NPC* npc) : ActionNode(parent), m_npc(npc)
        {
        }

        Status tick() override
        {
            m_npc->findValidTarget();
            if (m_npc->getCurrentTarget() == nullptr)
            {
                std::cout << "No enemy left!" << std::endl;
                return Failed;
            }

            std::cout << "Enemy spotted!" << std::endl;
            return Success;
        }

    private:
        NPC* m_npc;
    };

    class VictoryDance : public ActionNode
    {
    public:
        VictoryDance(CompositeNode* parent) : ActionNode(parent)
        {
        }

        Status tick() override
        {
            if (m_delay <= 0)
            {
                std::cout << std::endl;
                return Success;
            }
            std::vector<std::string> danceSteps = { "\\o/", "|o/", "\\o|", "-o-"};
            std::cout << danceSteps[m_delay % 4] << " ";
            m_delay--;

            return Running;
        }

    private:
        int m_delay = 12;
    };
}