#include "Player.h"

#include <iostream>
#include <array>
#include <fstream>

Player::Player(Scene& scene)
    : IGameObject(scene)
{
}

std::vector<IAttribute*> Player::getAllAttributes()
{
    return { &name, &PV, &strenght, &dexterity };
}

// Grace a la macro magique
//bool toto = [](){theGameObjectFactory().registerType<Player>(); return true; }();

// Equivalant a :
// bool tartempion()
// {
//     theGameObjectFactory().registerType<Player>();
//     return true;
// }
// 
// bool toto = tartempion();

DEFINE_GAME_OBJECT(Player)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                     