#include <SFML/Graphics.hpp>

std::vector<sf::Vector2f> getStarVertices(float radius, sf::Vector2f center, float angle)
{
    std::vector<sf::Vector2f> result;
    result.reserve(7);

    for (int i = 0; i < 7; ++i)
    {
        float alpha = 2.f * 3.1415926535f / 7.f * static_cast<float>(i);
        float x = radius * std::cos(alpha + angle);
        float y = radius * std::sin(alpha + angle);
        result.push_back(center + sf::Vector2f(x, y));
    }

    return result;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");
    window.setFramerateLimit(60);
    sf::CircleShape shape(300.f, 3);
    shape.setFillColor(sf::Color::Green);

    sf::RectangleShape rectangle(sf::Vector2f(200.f, 200.f));
    rectangle.setPosition(200.f, 200.f);
    rectangle.setFillColor(sf::Color::Blue);

    float angle = 0.f;

    sf::Texture texture;
    texture.loadFromFile("C:\\repoGC\\BeginningSFML\\Truc.bmp");

    sf::Sprite sprite;
    sprite.setTexture(texture);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        //window.draw(shape);
        //window.draw(rectangle);
        
        auto P = getStarVertices(200.f, sf::Vector2f(300.f, 300.f), angle);
        angle = angle + 0.01f;
        
        for (int i = 0; i < 7; ++i)
        {
            sf::RectangleShape rectangle(sf::Vector2f(3.f, 3.f));
            rectangle.setPosition(P[i]);
            rectangle.setFillColor(sf::Color::Red);
            window.draw(rectangle);
        }
        
        std::vector<sf::Vertex> lines;
        lines.reserve(14);

        int startIdx = 0;
        for (int i = 0; i < 7; ++i)
        {
            int endIdx = (startIdx + 3) % 7;
            lines.push_back(P[startIdx]);
            lines.push_back(P[endIdx]);
            startIdx = endIdx;
        }
        
        window.draw(&lines[0], 14, sf::Lines);

        sprite.setOrigin(64, 64);
        sprite.setRotation(-2.f * angle / 3.1415926f * 180.f);
        sprite.setPosition(300.f, 300.f);

        window.draw(sprite);

        window.display();
    }

    return 0;
}
