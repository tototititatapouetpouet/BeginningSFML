#include "IGameObject.h"

#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"

#include <stdexcept>

IGameObject::IGameObject(Scene& scene)
{
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

#include<iostream>
GameObjectFactory::GameObjectFactory()
{
    std::cout << "COucou!" << "\n";
}

GameObjectFactory maGameObjectFactory;
