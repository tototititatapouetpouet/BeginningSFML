#include "IGameObject.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"

#include <stdexcept>

IGameObject::IGameObject()
{
}



void GameObjectFactory::_registerType(const std::string& typeName, CreationRecipe fn)
{
    auto it = m_creationRecipes.find(typeName);
    if (it != m_creationRecipes.end())
        throw std::runtime_error("Warning trying to register a type twice!");

    m_creationRecipes[typeName] = fn;
}

IGameObject* GameObjectFactory::create(const std::string& typeName)
{
    auto it = m_creationRecipes.find(typeName);
    if (it == m_creationRecipes.end())
        throw std::runtime_error("Warning trying to create an unregistered entity type!");

    return it->second();
}

GameObjectFactory& theGameObjectFactory()
{
    static GameObjectFactory factory;
    return factory;
}

GameObjectFactory::GameObjectFactory()
{
    //registerType<Player>();
    registerType<Enemy>();
    registerType<Enemy2>();
    registerType<Boss>();
}

