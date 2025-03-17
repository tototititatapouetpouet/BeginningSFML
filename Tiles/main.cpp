#include <SFML/Graphics.hpp>



using MapRepresentation = std::vector<std::string>;
MapRepresentation repr = {
    "TTTTTTHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "TTHHHHHFHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "THHFHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "TTHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "THHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "THHHHHHHFHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "THHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "THHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHT"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFT"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHFFT"
  , "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHTTTT"
};

class View
{
public:
    View(float width_, float height_, float posX_, float posY_) : width(width_), height(height_), posX(posX_), posY(posY_), targetX(posX_), targetY(posY_)
    { }

    void update()
    {
        float factor = 0.01f;
        posX = (1.f - factor) * posX + factor * targetX;
        posY = (1.f - factor) * posY + factor * targetY;
    }

public:
    float width;
    float height;
    float posX;
    float posY;
    float targetX;
    float targetY;
    float scale = 1.0f;
};

class TilesMap
{
public:
    TilesMap(const MapRepresentation& repr) : m_width(0), m_height(0)
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

    using TileType = char;

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

    void render(sf::RenderWindow& w, const View& view)
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

private:
    TileType& getTile(int row, int col) { return m_tiles[row * m_width + col]; }
    const TileType& getTile(int row, int col) const { return m_tiles[row * m_width + col]; }

    std::vector<TileType> m_tiles;

    sf::Texture m_texture;

    int m_width;
    int m_height;
    int m_tileSize;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "SFML works!");

    View view(1000, 1000, 0, 0);

    TilesMap tm(repr);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    view.targetY -= 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    view.targetY += 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                {
                    view.targetX -= 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                {
                    view.targetX += 10;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
                {
                    view.scale *= 1.1f;
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
                {
                    view.scale /= 1.1f;
                }
            }
        }

        view.update();

        window.clear();
        tm.render(window, view);
        window.display();
    }

    return 0;
}