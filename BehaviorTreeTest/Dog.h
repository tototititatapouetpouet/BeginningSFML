#pragma once

#include "NPC.h"

class Food : public IGameObject
{ };

class Dog : public IGameObject
{
public:
    void spotFood();

    void goTo(IGameObject* location);

    void eatSpottedFood();
};

class Game2
{
public:
    void exec();

    std::array<Food, 6> m_miams;
    Dog dog;
};
