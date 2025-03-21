#pragma once

#include <string>

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
