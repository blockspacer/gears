#ifndef MAP_HPP
#define MAP_HPP

#include "MapRenderer.hpp"
#include "Tile.hpp"

#include "include/PerlinNoise.hpp"

#include <vector>

namespace ge {

class Map : private TileProvider
{
public:
    Map();
    ~Map();

    void save();

    // update map
    void update(float dt);
    // draw map
    void draw(sf::RenderTarget& rt) const;

    // get tile reference by grid position
    Tile& tile(const sf::Vector2i& pos);
    // get tile reference by grid position
    Tile& tile(int x, int y);

    // get tile reference by world position
    Tile& tileAt(const sf::Vector2f& pos);
    // get tile reference by world position
    Tile& tileAt(float x, float y);


protected:
    // supplement the map renderer with tile information
    void provideTile(int x, int y, int layer, sf::Color& color, sf::IntRect& src);

    // numerical random seed of the map
    sf::Uint32 m_seed;
    // open simplex noise context
    PerlinNoise m_perlinNoise;
    // map limits
    sf::IntRect m_bounds;
    // the data structure for the tiles in the map
    std::vector<std::vector<std::unique_ptr<Tile>>> m_grid;
    // the texture in which tile images are stored
    sf::Texture* m_tileSet;
    // the class that does all the rendering of the map
    MapRenderer m_renderer;
};

} //end ns

#endif // MAP_HPP
