#include "IGameObject.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"

#include <stdexcept>

IGameObject::IGameObject(Scene& scene) : m_position(0, 0)
{
}

void IGameObject::setPosition(const Vec2f& position)
{
    m_position = position;
}

const Vec2f& IGameObject::getPosition() const
{ 
    return m_position;
}

void GameObjectFactory::_registerType(const std::string& typeName, CreationRecipe fn)
{
    auto it = m_creationRecipes.find(typeName);
    if (it != m_creationRecipes.end())
        throw std::runtime_error("Warning trying to register a type twice!");

    m_creationRecipes[typeName] = fn;
}

IGameObject* GameObjectFactory::create(const std::string& typeName, Scene& scene)
{
    auto it = m_creationRecipes.find(typeName);
    if (it == m_creationRecipes.end())
        throw std::runtime_error("Warning trying to create an unregistered entity type!");

    CreationRecipe fn = it->second;
    return fn(scene);
}

GameObjectFactory& theGameObjectFactory()
{
    static GameObjectFactory factory;
    return factory;
}

GameObjectFactory::GameObjectFactory()
{
}
