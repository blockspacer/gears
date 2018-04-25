// MapRenderer.cpp

#include "MapRenderer.hpp"
#include "stdafx.hpp"

MapRenderer::MapRenderer(sf::Texture*  texture,
                         TileProvider* provider,
                         int           tileSize,
                         int           layers)
{
    if(provider == nullptr || layers <= 0)
        throw "hey";
    this->texture  = texture;
    this->provider = provider;
    this->tileSize = tileSize;
    this->layers   = layers;
}
MapRenderer::~MapRenderer(void)
{
}
int MapRenderer::getTileSize() const
{
    return tileSize;
}
int MapRenderer::getLayers() const
{
    return layers;
}

/// redraw every tile on screen
void MapRenderer::refreshAll()
{
    refreshLocal(0, 0, width, height);
}

/// redraw part of screen
void MapRenderer::refreshLocal(int left, int top, int right, int bottom)
{
    for(int y = top; y < bottom; y++)
        for(int x = left; x < right; x++)
            refreshTile(x + offset.x, y + offset.y);
}

/// adjust amount of vertices to size of the screen
void MapRenderer::setSize(sf::Vector2f v)
{
    int w = static_cast<int>(v.x / tileSize) + 2;
    int h = static_cast<int>(v.y / tileSize) + 2;
    if(w == width && h == height)
        return;

    width  = w;
    height = h;

    std::size_t size = 4 * width * height * layers;
    // allocate quad per tile per layer
    if(vertices.size() < size) {
        vertices.resize(size);
    }
    refreshAll();
}

/// refresh parts of screen if player moved
void MapRenderer::setCorner(sf::Vector2f v)
{
    auto tile = getTile(v);
    auto dif  = tile - offset;
    if(dif.x == 0 && dif.y == 0)
        return;    // player didnt moved, no need to update anything
    offset = tile; // offset is a tile position in the left top corner

    if(abs(dif.x) > width / 4 || abs(dif.y) > height / 4) {
        // if difference is too big, we simply redraw everyting
        refreshAll();
    } else {
        // if player moved right, refresh colum on the right side of the screen
        if(dif.x > 0) {
            refreshLocal(width - dif.x, 0, width, height);
        }
        // and vice versa
        else {
            refreshLocal(0, 0, -dif.x, height);
        }
        // same if player moved top/ bottom
        if(dif.y > 0) {
            refreshLocal(0, height - dif.y, width, height);
        } else {
            refreshLocal(0, 0, width, -dif.y);
        }
    }
}
/// take world position and return tile indexes
sf::Vector2i MapRenderer::getTile(sf::Vector2f pos) const
{
    int x = static_cast<int>(pos.x / tileSize);
    int y = static_cast<int>(pos.y / tileSize);
    if(pos.x < 0)
        x--;
    if(pos.y < 0)
        y--;
    return sf::Vector2i(x, y);
}
/// draw textured quad on given position
void MapRenderer::drawQuad(int index, sf::FloatRect rec, sf::IntRect src, sf::Color color)
{
    sf::FloatRect srcF((float)src.left, (float)src.top, (float)src.width, (float)src.height);

    auto ptr         = &vertices[index];
    ptr->position.x  = rec.left;
    ptr->position.y  = rec.top;
    ptr->texCoords.x = srcF.left;
    ptr->texCoords.y = srcF.top;
    ptr->color       = color;
    ptr++;

    ptr->position.x  = rec.left + rec.width;
    ptr->position.y  = rec.top;
    ptr->texCoords.x = srcF.left + srcF.width;
    ptr->texCoords.y = srcF.top;
    ptr->color       = color;
    ptr++;

    ptr->position.x  = rec.left + rec.width;
    ptr->position.y  = rec.top + rec.height;
    ptr->texCoords.x = srcF.left + srcF.width;
    ptr->texCoords.y = srcF.top + srcF.height;
    ptr->color       = color;
    ptr++;

    ptr->position.x  = rec.left;
    ptr->position.y  = rec.top + rec.height;
    ptr->texCoords.x = srcF.left;
    ptr->texCoords.y = srcF.top + srcF.height;
    ptr->color       = color;
}

/// redraw quads that belong to given tile
void MapRenderer::refreshTile(int x, int y)
{
    if(x < offset.x || x >= (offset.x + width) || y < offset.y || y >= (offset.y + height)) {
        return; // check if tile is visible
    }

    // vertices works like 2d ring buffer
    auto vx = x % width;
    auto vy = y % height;
    if(vx < 0)
        vx += width;
    if(vy < 0)
        vy += height;
    // we can do this, because some tiles are never to be seen at once

    auto index = (vx + vy * width) * 4 * layers;
    auto rec   = sf::FloatRect((float)x * tileSize, (float)y * tileSize, (float)tileSize, (float)tileSize);

    for(int i = 0; i < layers; i++) {
        sf::Color   color;
        sf::IntRect src;
        provider->provideTile(x, y, i, color, src);
        // get color and texture rectangle from our providing function

        drawQuad(index, rec, src, color);
        // insert quad in vertex array
        index += 4;
    }
}
/// draw map on screen
void MapRenderer::draw(sf::RenderTarget& rt, sf::RenderStates states) const
{
    states.texture = texture;
    rt.draw(&vertices[0], vertices.size(), sf::PrimitiveType::Quads, states);
}

/// update screen size and position of camera
void MapRenderer::update(sf::RenderTarget& rt)
{
    auto view = rt.getView();
    setSize(view.getSize());
    setCorner(rt.mapPixelToCoords(sf::Vector2i()));
}
