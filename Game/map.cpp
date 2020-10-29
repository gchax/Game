#include "map.h"

tilemap::tilemap()
{
}

tilemap::~tilemap()
{
}

bool tilemap::load(const string& tileset, Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) 
{
    if (!m_tileset.loadFromFile(tileset))
        return false;

    m_vertices.setPrimitiveType(Quads);
    m_vertices.resize(width * height * 4);

    for (unsigned int i = 0; i < width; ++i)
        for (unsigned int j = 0; j < height; ++j)
        {
            int tileNumber = tiles[i + j * width];

            int tu = tileNumber % (m_tileset.getSize().x / tileSize.x);
            int tv = tileNumber / (m_tileset.getSize().x / tileSize.x);

            Vertex* quad = &m_vertices[(i + j * width) * 4];

            quad[0].position = Vector2f(i * tileSize.x, j * tileSize.y);
            quad[1].position = Vector2f((i + 1) * tileSize.x, j * tileSize.y);
            quad[2].position = Vector2f((i + 1) * tileSize.x, (j + 1) * tileSize.y);
            quad[3].position = Vector2f(i * tileSize.x, (j + 1) * tileSize.y);

            quad[0].texCoords = Vector2f(tu * tileSize.x, tv * tileSize.y);
            quad[1].texCoords = Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
            quad[2].texCoords = Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
            quad[3].texCoords = Vector2f(tu * tileSize.x, (tv + 1) * tileSize.y);
        }
    return true;
}