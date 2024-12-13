#pragma once

#include "TextureCache.h"

#include <SFML/Graphics.hpp>

class IGameObject;

#define private_members private
#define private_function private
#define private_friend_function(Cls) private

class Game
{
public:
    friend class IGameObject;

    Game();
    ~Game();

    void handleInputs();

    void update();

    void render();

    void run();

    TextureCache& getTextureCache();

private_function:
    void detectCollision();
    void onCollision(IGameObject* go1, IGameObject* go2);
    void renderBoundingBox();

//  Those 4 functions only intend to be called by IGameObject.
private_friend_function(IGameObject):
    void _addObject(IGameObject*);
    void _removeObject(IGameObject*);
    void _toBeRemoveObject(IGameObject*);
    void _deferedAddObject(IGameObject*);
    void _deferedAddObjects();
    void _cleanObject();

private_members:
    sf::RenderWindow m_window;
    std::vector<IGameObject*> m_allGameObjects;
    std::vector<IGameObject*> m_toBeRemovedGameObjects;
    std::vector<IGameObject*> m_toBeAddedGameObjects;
    TextureCache m_textureCache;
};
