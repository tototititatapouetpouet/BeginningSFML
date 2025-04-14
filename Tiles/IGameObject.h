#pragma once

#include <string>
#include <functional>
#include <sstream>
#include <fstream>
#include <map>

using GameObjectType = std::string;
class Scene;


struct Vec2f
{
    Vec2f(float x_ = 0.f, float y_ = 0.f) : x(x_), y(y_) {}

    float x, y;
};

struct IAttribute
{
    IAttribute(const std::string name) : m_name(name) {}
    virtual ~IAttribute() = default;

    virtual void save(std::ofstream& file) = 0;
    virtual void load(const std::string& value) = 0;
    const std::string& getName() const { return m_name; }

private:
    std::string m_name;
};

template<typename AttributeType>
struct Attribute : public IAttribute
{
    Attribute(const std::string name, const AttributeType& value) : IAttribute(name), m_value(value) {}

    void save(std::ofstream& file) override
    {
        file << m_value;
    }

    void load(const std::string& value) override
    {
        std::istringstream iss(value);
        iss >> m_value;
    }

private:
    AttributeType m_value;
};

class IGameObject
{
public:
    IGameObject(Scene& scene);

    virtual ~IGameObject() = default;

    virtual GameObjectType getGameObjectType() const = 0;

    void setPosition(const Vec2f& position);
    const Vec2f& getPosition() const;

    virtual void saveAttributes(std::ofstream& file) = 0;
    
    using AttributesDict = std::map<std::string, std::string>;
    virtual void loadAttributes(const AttributesDict& attributes) = 0;

private:
    Vec2f m_position;
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
