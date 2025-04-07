#include "TilesMap.h"

#include "View.h"

#include <SFML/Graphics.hpp>

#include <map>

MapRepresentation getRepresentationFromFile(std::ifstream& file)
{
    int nbLine;
    file >> nbLine;

    MapRepresentation theMap;
    for (int i = 0; i < nbLine; ++i)
    {
        std::string theLine;
        file >> theLine;
        theMap.push_back(theLine);
    }

    return theMap;
}

MapRepresentation TilesMap::getRepr() const
{
    MapRepresentation retVal;
    retVal.resize(m_height);

    for (int row = 0; row < m_height; ++row)
    {
        retVal[row].resize(m_width);
        for (int col = 0; col < m_width; ++col)
        {
            retVal[row][col] = getTile(row, col);
        }
    }
    return retVal;
}

TilesMap::TilesMap(const MapRepresentation& repr) : m_width(0), m_height(0)
{
    m_width = static_cast<int>(repr[0].size());
    m_height = static_cast<int>(repr.size());
    m_tileSize = 32;

    m_tiles.resize(m_width * m_height);

    for (int row = 0; row < m_height; ++row)
    {
        for (int col = 0; col < m_width; ++col)
        {
            getTile(row, col) = repr[row][col];
        }
    }

    m_texture.loadFromFile("tileset.png");
}

sf::Vector2i getTileCoordinateInTexture(const TileType& tile)
{
    static std::map<TileType, sf::Vector2i> tileMap = {
        {'H', {0,  0} }
      , {'F', {0,  3} }
      , {'T', {12, 6} }
    };

    auto it = tileMap.find(tile);
    if (it == tileMap.end())
        throw;

    return it->second;
}

int clamp(int min, int max, int val)
{
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}

const int& TilesMap::getTileSize() const
{
    return m_tileSize;
}

void TilesMap::setTile(int row, int col, const TileType& tile)
{
    getTile(row, col) = tile;
}

bool TilesMap::setTileSafe(int row, int col, const TileType& tile)
{
    if ((row < 0) || (row >= m_height) || (col < 0) || (col >= m_width))
        return false;

    setTile(row, col, tile);
    return true;
}

void TilesMap::render(sf::RenderWindow& w, const View& view)
{
    float tileSizeInScreen = m_tileSize * view.scale;

    int beginTileX = static_cast<int>(view.posX / tileSizeInScreen);
    int beginTileY = static_cast<int>(view.posY / tileSizeInScreen);

    int nbTileX = static_cast<int>(std::ceil(static_cast<float>(view.width) / tileSizeInScreen));
    int nbTileY = static_cast<int>(std::ceil(static_cast<float>(view.height) / tileSizeInScreen));

    int endTileX = beginTileX + nbTileX;
    int endTileY = beginTileY + nbTileY;

    beginTileX = clamp(0, m_width - 1, beginTileX);
    endTileX = clamp(0, m_width - 1, endTileX);

    beginTileY = clamp(0, m_height - 1, beginTileY);
    endTileY = clamp(0, m_height - 1, endTileY);


    for (int row = beginTileY; row <= endTileY; ++row)
    {
        for (int col = beginTileX; col <= endTileX; ++col)
        {
            sf::Vector2f screenPos = sf::Vector2f(tileSizeInScreen * col - view.posX, tileSizeInScreen * row - view.posY);

            sf::Vector2i tilePosInTex = m_tileSize * getTileCoordinateInTexture(getTile(row, col));
            sf::Sprite sprite(m_texture, sf::IntRect{ tilePosInTex, {m_tileSize, m_tileSize} });
            sprite.setScale(view.scale, view.scale);
            sprite.setPosition(screenPos);
            w.draw(sprite);
        }
    }
}