#include "Tree.h"

namespace BT
{
    IComponentNode::IComponentNode(CompositeNode* parent)
        : m_parent(nullptr)
    {
        setParent(parent);
    }

    IComponentNode::~IComponentNode()
    {
        setParent(nullptr);
    }

    void IComponentNode::setParent(CompositeNode* newParent)
    {
        if (m_parent)
            m_parent->remove(this);

        m_parent = newParent;

        if (m_parent)
            m_parent->add(this);
    }
}

void NPC::findValidTarget()
{
    for (auto& enemy : m_game.enemies)
    {
        if (enemy.PV > 0)
        {
            m_currentTarget = &enemy;
            return;
        }
    }

    m_currentTarget = nullptr;
}

