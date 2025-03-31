#pragma once

#include <string>
#include <functional>
#include <map>

using GameObjectType = std::string;

struct IGameObject
{
    IGameObject();

    virtual ~IGameObject() = default;

    virtual GameObjectType getGameObjectType() const = 0;
};

#define DECLARE_GAME_OBJECT()       \
GameObjectType getGameObjectType() const override; \
static std::string className();

#define DEFINE_GAME_OBJECT(TheClassName) \
GameObjectType TheClassName::getGameObjectType() const { return className(); } \
std::string TheClassName::className() { return #TheClassName; }




class GameObjectFactory
{
public:
    GameObjectFactory();

    using CreationRecipe = std::function<IGameObject* ()>;
    void _registerType(const std::string& typeName, CreationRecipe fn);
    IGameObject* create(const std::string& typeName);

    template<typename GameObjectType>
    void registerType()
    {
        _registerType(GameObjectType::className(), []() ->IGameObject* { return new GameObjectType; });
    }

private:
    std::map<std::string, CreationRecipe> m_creationRecipes;
};

GameObjectFactory& theGameObjectFactory();
