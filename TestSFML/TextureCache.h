#pragma once

#include <vector>
#include <string>

namespace sf { class Texture; }

class TextureCache
{
public:
    sf::Texture& getTexture(const std::string& path);
    ~TextureCache();

private:
    struct TextureInfo
    {
        sf::Texture* texture;
        std::string path;
    };

    std::vector<TextureInfo> m_allTextureInfos;
};
