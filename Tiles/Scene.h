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

    void save(const std::string& outputLevelFilePath) const;

    View& getView() { return m_view; }
    const View& getView() const { return m_view; }

    void click(int x, int y);

private:
    std::vector<IGameObject*> m_allGameObjects;
    TilesMap* m_decor;
    View m_view;

public:
    int m_selectedTileIdx = 0;
};
