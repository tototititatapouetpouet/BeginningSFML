#include "TextureCache.h"

#include <SFML/Graphics.hpp>

TextureCache::~TextureCache()
{
    for (auto& textureInfo : m_allTextureInfos)
        delete textureInfo.texture;
}

sf::Texture& TextureCache::getTexture(const std::string& path)
{
    for (auto& textureInfo : m_allTextureInfos)
    {
        if (textureInfo.path == path)
            return *textureInfo.texture;
    }

    TextureInfo ti;
    ti.path = path;
    ti.texture = new sf::Texture;
    ti.texture->loadFromFile(path);
    m_allTextureInfos.push_back(ti);

    return *ti.texture;
}
