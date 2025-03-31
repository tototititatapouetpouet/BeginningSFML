#pragma once

class View
{
public:
    View(float width_, float height_, float posX_, float posY_) : width(width_), height(height_), posX(posX_), posY(posY_), targetX(posX_), targetY(posY_)
    {
    }

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
