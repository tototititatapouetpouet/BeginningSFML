#include "IGameObject.h"

#include "Game.h"

IGameObject::IGameObject(Game& game) : m_game(game)
{
    m_game._addObject(this);
}

IGameObject::~IGameObject()
{
    m_game._removeObject(this);
}

void IGameObject::destroy()
{
    m_game._toBeRemoveObject(this);
}
