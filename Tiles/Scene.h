#pragma once

#include "View.h"

#include <string>
#include <vector>

class IGameObject;
class TilesMap;

namespace sf
{
    class RenderWindow;
}

class Scene
{
public:
    Scene(const std::string& inputLevelFilePath);

    void render(sf::RenderWindow& w);

    View& getView() { return m_view; }
    const View& getView() const { return m_view; }

private:
    std::vector<IGameObject*> m_allGameObjects;
    TilesMap* m_decor;
    View m_view;
};
