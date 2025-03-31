#include "Player.h"

#include <iostream>

Player::Player()
    : IGameObject()
{
}

bool registerPlayer = []() {theGameObjectFactory().registerType<Player>(); return true; }();

DEFINE_GAME_OBJECT(Player)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                     