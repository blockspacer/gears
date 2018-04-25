#include "Map.hpp"
#include "stdafx.hpp"

#include <exception>
#include <iostream>

namespace ge {

using namespace sf;

Map::Map()
    : m_seed(706339715)
    , m_perlinNoise(m_seed)
    , m_bounds(-100, -100, 200, 200) // left, top, width, height
    , m_tileSet(new Texture)
    , m_renderer(m_tileSet, this, 16, 3)
{
    std::cout << "== Creating map ==" << std::endl;
    // thor::StopWatch initTime;
    // initTime.start();

    static const double magick = 0.06706339715;

    m_tileSet->loadFromFile("res/img/tileset32.png");

    for(int x = 0; x < m_bounds.width; x++) {
        m_grid.push_back(std::vector<std::unique_ptr<Tile>>());
        for(int y = 0; y < m_bounds.height; y++) {
            double val = m_perlinNoise.multiNoise2d((double)x * magick, (double)y * magick, 3);
            m_grid.back().push_back(std::make_unique<Tile>(
                sf::Vector2i(x - m_bounds.left, y - m_bounds.top),
                (val > 0.4) ? Tile::STONE : Tile::AIR, this));
            // m_grid.back().back()->setLightSource()
        }
    }
}

Map::~Map()
{
    delete m_tileSet;
}

void Map::update(float dt)
{
}

void Map::render(sf::RenderTarget& rt)
{
    m_renderer.update(rt);
}

void Map::draw(sf::RenderTarget& rt) const
{
    m_renderer.draw(rt, sf::RenderStates::Default);
}

Tile& Map::tile(const sf::Vector2i& pos)
{
    if(m_bounds.contains(pos)) {
        return *m_grid[pos.x - m_bounds.left][pos.y - m_bounds.top].get();
    }
    throw std::out_of_range("Requested tile is out of map bounds: ( " +
                            std::to_string(pos.x) + "; " +
                            std::to_string(pos.y) + ")");
}

Tile& Map::tile(int x, int y)
{
    return tile(sf::Vector2i(x, y));
}

Tile& Map::tileAt(const sf::Vector2f& pos)
{
    return tile(toVec2i(pos / 16.f));
}

Tile& Map::tileAt(float x, float y)
{
    return tileAt(sf::Vector2f(x, y));
}

void Map::provideTile(int x, int y, int layer, Color& color, IntRect& src)
{
    if(m_bounds.contains(x, y)) {
        tile(x, y).provide(color, src);
    } else {
        color = sf::Color::Black;
    }
}


} //end ns
