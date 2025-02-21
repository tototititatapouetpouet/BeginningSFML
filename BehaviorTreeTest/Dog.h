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

    void bark();
};

//  Eat every food available.
//      -> locate food
//      -> go to food
//      -> eat food
//  One there is no food left, bark for more of it!

class Game2
{
public:
    void exec();

    std::array<Food, 6> m_miams;
    Dog dog;
};
