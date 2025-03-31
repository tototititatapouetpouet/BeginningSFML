#include "Player.h"

#include <iostream>

Player::Player(Scene& scene)
    : IGameObject(scene)
{
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
                                                                                                                                                                                                                                                                                                                                                                                                                                                                     