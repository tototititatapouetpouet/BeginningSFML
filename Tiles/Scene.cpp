#include "Scene.h"

#include "IGameObject.h"
#include "TilesMap.h"

#include <fstream>

std::vector<IGameObject*> getAllGameObjectFromFile(std::ifstream& file, Scene& scene)
{
    std::vector<IGameObject*> result;

    while (!file.eof())
    {
        std::string line;
        int px;
        int py;
        file >> line >> px >> py;

        if (line.empty())
            continue;

        result.push_back(theGameObjectFactory().create(line, scene));
    }

    return result;
}

Scene::Scene(const std::string& inputLevelFilePath) : m_view(1000, 1000, 0.0f, 0.0f)
{
    std::ifstream file(inputLevelFilePath);
    
    auto mapRepr = getRepresentationFromFile(file);
    m_decor = new TilesMap(mapRepr);

    m_allGameObjects = getAllGameObjectFromFile(file, *this);
}

void Scene::render(sf::RenderWindow& w)
{
    m_decor->render(w, m_view);
}
