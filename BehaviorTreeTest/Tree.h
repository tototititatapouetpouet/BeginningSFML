#pragma once

#include <iostream>
#include <vector>
#include <type_traits>

class CompositeNode;

struct IComponentNode
{
    IComponentNode(CompositeNode* parent = nullptr);

    void setParent(CompositeNode* newParent);

    virtual ~IComponentNode();

    virtual void display() = 0;

protected: 
    CompositeNode* m_parent;
};

struct LeafNode : IComponentNode
{
    LeafNode(CompositeNode* node = nullptr)
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

