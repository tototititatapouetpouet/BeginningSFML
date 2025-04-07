#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>
#include <fstream>

using MapRepresentation = std::vector<std::string>;
MapRepresentation getRepresentationFromFile(std::ifstream& file);

using TileType = char;

class View;

class TilesMap
{
public:
    TilesMap(const MapRepresentation& repr);

    void render(sf::RenderWindow& w, const View& view);

    MapRepresentation getRepr() const;

    const int& getTileSize() const;

    TileType& getTile(int row, int col) { return m_tiles[row * m_width + col]; }
    const TileType& getTile(int row, int col) const { return m_tiles[row * m_width + col]; }
    void setTile(int row, int col, const TileType& tile);
    bool setTileSafe(int row, int col, const TileType& tile);

private:
    std::vector<TileType> m_tiles;

    sf::Texture m_texture;

    int m_width;
    int m_height;
    int m_tileSize;
};