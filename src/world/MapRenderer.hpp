#include <SFML/Graphics.hpp>

/// callback function that will provide data for each tile
class TileProvider
{
    friend class MapRenderer;

protected:
    virtual void provideTile(int x, int y, int layer,
                             sf::Color&   color,
                             sf::IntRect& rect) = 0;
};

/// provides fast rendering of tilemaps
class MapRenderer : public sf::Drawable
{
public:
    MapRenderer(sf::Texture*  texture,
                TileProvider* provider,
                int          tileSize = 16,
                int          layers   = 1);
    ~MapRenderer(void);
    int         getTileSize() const;
    int         getLayers() const;
    sf::Vector2i getTile(sf::Vector2f pos) const;

    void refreshAll();
    void refreshTile(int x, int y);
    void draw(sf::RenderTarget& rt, sf::RenderStates states) const;
    void update(sf::RenderTarget& rt);

private:
    int width;
    int height;
    int tileSize;
    int layers;

    std::vector<sf::Vertex> vertices;
    sf::Vector2i            offset;

    TileProvider* provider;
    sf::Texture*  texture;

    void setSize(sf::Vector2f v);
    void setCorner(sf::Vector2f v);
    void drawQuad(int index, sf::FloatRect rec, sf::IntRect src, sf::Color color);
    void refreshLocal(int left, int top, int right, int bottom);
};
