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
        float px;
        float py;
        file >> line >> px >> py;

        if (line.empty())
            continue;

        auto* gameObject = theGameObjectFactory().create(line, scene);
        gameObject->setPosition(Vec2f(px, py));
        result.push_back(gameObject);
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

void Scene::click(int x, int y)
{
    // TODO : On prend le temps de faire la conversion screen space to world space.
    //        Ensuite, on fait la conversion world space vers tuile index.
    float worldCoordX = (static_cast<float>(x) + m_view.posX) / m_view.scale;
    float worldCoordY = (static_cast<float>(y) + m_view.posY) / m_view.scale;

    int tileCol = worldCoordX / m_decor->getTileSize();
    int tileRow = worldCoordY / m_decor->getTileSize();

    m_decor->setTileSafe(tileRow, tileCol, 'T');
}

void Scene::save(const std::string& outputLevelFilePath) const
{
    std::ofstream file(outputLevelFilePath);

    auto mapRepr = m_decor->getRepr();
    file << mapRepr.size() << "\n";
    for (const auto& line : mapRepr)
        file << line << "\n";

    file << "\n";

    for (const auto& gameObject : m_allGameObjects)
    {
        file << gameObject->getGameObjectType() << " " << gameObject->getPosition().x << " " << gameObject->getPosition().y;
        file << "\n";
    }
}

void Scene::render(sf::RenderWindow& w)
{
    m_decor->render(w, m_view);
}
