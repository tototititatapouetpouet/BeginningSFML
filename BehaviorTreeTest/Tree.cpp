#include "Tree.h"

namespace BT
{
    IComponentNode::IComponentNode(ICompositeNode* parent)
        : m_parent(nullptr)
    {
        setParent(parent);
    }

    IComponentNode::~IComponentNode()
    {
        setParent(nullptr);
    }

    void IComponentNode::setParent(ICompositeNode* newParent)
    {
        if (m_parent)
            m_parent->remove(this);

        m_parent = newParent;

        if (m_parent)
            m_parent->add(this);
    }

    ICompositeNode* IComponentNode::getParent() { return m_parent; }
    const ICompositeNode* IComponentNode::getParent() const { return m_parent; }

    NPC* IComponentNode::getNpc()
    {
        return getRootNode()->getNpc();
    }

    const NPC* IComponentNode::getNpc() const
    {
        return getRootNode()->getNpc();
    }

    RootNode* IComponentNode::getRootNode()
    {
        auto* currentPtr = this;
        while (currentPtr->getParent() != nullptr)
            currentPtr = currentPtr->getParent();

        return static_cast<RootNode*>(currentPtr);
    }

    const RootNode* IComponentNode::getRootNode() const
    {
        const auto* currentPtr = this;
        while (currentPtr->getParent() != nullptr)
            currentPtr = currentPtr->getParent();

        return static_cast<const RootNode*>(currentPtr);
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

