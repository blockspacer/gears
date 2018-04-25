#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/System.hpp>

namespace ge {

class Map;

class Tile
{
public:
    static const Tile Invalid;

    enum TileId
    {
        INVALID = -1,
        AIR     = 0,
        STONE,
        DIRT,
        GRASS,
    };

    Tile(sf::Vector2i position = sf::Vector2i(),
         TileId       tileId   = TileId::INVALID,
         Map*         parent   = nullptr);

    ~Tile();

    /**
     * Called when creating tile from within the game
     */
    virtual void create();

    /**
     * Called when destroying tile from within the game
     * Implement dropped items and unexpected consequences here
     */
    virtual void destroy();

    /**
     * Called by the map to update parts of the world
     * May call other tile's tileUpdate recursively
     */
    virtual void tileUpdate();

    /**
     * provide the caller with information about how to display the tile
     * @color: the color of the tile gets written into it
     * @rect: the rect on the tileset of this tile's texture gets written in it
     */
    void provide(sf::Color& color, sf::IntRect& rect);

    /**
     * Set the amount of light this tile emits
     * causes lightUpdate call chains
     * @lightValue: the amount of light this tile emits
     */
    void setLightSource(sf::Uint8 lightValue);

    /**
     * Called recursively to update the light component of tiles
     * @lightValue: the amount of light this tile gets
     */
    void lightUpdate(sf::Uint8 lightValue);

    /**
     * Returns the TileId of the tile
     */
    TileId getId();

    /**
     * Returns the position the tile occupies on the map
     */
    sf::Vector2i getPosition();

    /**
     * Returns if the tile is solid or not
     */
    bool isSolid();

    /**
     * Returns the total damage amount the tile has taken;
     */
    sf::Uint16 getDamage();

    /**
     * Returns the percent of damage the tile has taken before being destroyed
     * 0 = no damage, 1 = destroyed
     */
    float getDamagePercent();

    /**
     * Set damage of the tile to the given value
     * if damage exceeds treshold, tile will be destroyed
     * @newDamage: the amount of damage to set
     */
    void setDamage(sf::Uint16 newDamage);

    /**
     * Set damage of the tile to the given percentage
     * if value is equal to greater than 1, tile will be destroyed
     * @newDamage: the percentage of damage to set (0 = no damage, 1 = destroyed)
     */
    void setDamagePercent(float newDamage);

    /**
     * Cause some amount of damage to the tile
     * if total damage exceeds treshold, tile will be destroyed
     * @damage: the amount of damage to cause
     */
    void applyDamage(sf::Uint16 damage);

protected:
    Map* m_parentMap;

    TileId             m_tileId; // What kind of tile is this
    const sf::Vector2i m_pos;    // place of the tile in the world
    bool               m_solid;  // if tile is solid

    sf::Uint16 m_damage;      // current damage; 0 = no damage
    sf::Uint16 m_damageLimit; // Damage the tile can take before being destroyed;

    sf::Uint8 m_lightLevel;  // Amount of light on tile
    sf::Uint8 m_lightSource; // Amount of light emitted by tile
    sf::Uint8 m_lightDecay;  // Amount of light this tile absorbs

    sf::Color   m_color;
    sf::IntRect m_tilemapRect;

    struct saveFormat
    {
        sf::Uint16 tileId;
        sf::Uint16 damage;
        sf::Uint16 flags;
        sf::Uint8  customData;
        sf::Uint8  enchanted;
        sf::Uint8  runed;
        sf::Uint8  reinforced;
    };
};

} // end ns

#endif //TILE_HPP
