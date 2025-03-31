#pragma once

#include <string>
#include <functional>
#include <map>

using GameObjectType = std::string;
class Scene;

class IGameObject
{
public:
    IGameObject(Scene& scene);

    virtual ~IGameObject() = default;

    virtual GameObjectType getGameObjectType() const = 0;
};

#define DECLARE_GAME_OBJECT()       \
GameObjectType getGameObjectType() const override; \
static std::string className();

#define DEFINE_GAME_OBJECT(TheClassName) \
GameObjectType TheClassName::getGameObjectType() const { return className(); } \
std::string TheClassName::className() { return #TheClassName; } \
bool register##TheClassName = [](){theGameObjectFactory().registerType<TheClassName>(); return true; }();




class GameObjectFactory
{
public:
    GameObjectFactory();

    using CreationRecipe = std::function<IGameObject* (Scene&)>;

    void _registerType(const std::string& typeName, CreationRecipe fn);
    IGameObject* create(const std::string& typeName, Scene& scene);

    template<typename GameObjectType>
    void registerType()
    {
        _registerType(GameObjectType::className(), [](Scene& scene) -> IGameObject* { return new GameObjectType(scene); });
    }

private:
    std::map<std::string, CreationRecipe> m_creationRecipes;
};

GameObjectFactory& theGameObjectFactory();
