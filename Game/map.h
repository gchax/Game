#pragma once
#include "stdfn.h"

class tilemap : public Drawable, public Transformable, public Texture
{
public:
    tilemap();
    ~tilemap();

    bool load(const string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height);

private:

    virtual void draw(RenderTarget& target, RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &m_tileset;
        target.draw(m_vertices, states);
    }

    VertexArray m_vertices;
    Texture m_tileset;
};