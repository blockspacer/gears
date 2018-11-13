#include "stdafx.hpp"

#include "Tile.hpp"

#include "Map.hpp"

namespace ge {

const Tile Tile::Invalid = Tile();

Tile::Tile(sf::Vector2i position, TileId tileId, Map* parent)
    : m_pos(position)
    , m_tileId(tileId)
    , m_parentMap(parent)
    , m_solid(true)
    , m_damage(0)
    , m_damageLimit(0)
    , m_lightLevel(0)
    , m_lightSource(0)
    , m_lightDecay(m_solid ? 32 : 8)
{
    switch(m_tileId) {
    case Tile::INVALID:
    case Tile::AIR:
        m_color       = sf::Color::Transparent;
        m_tilemapRect = sf::IntRect(0, 0, 32, 32);
        break;
    case Tile::STONE:
        m_color       = sf::Color(129, 135, 138);
        m_tilemapRect = sf::IntRect(96, 160, 32, 32);
        // m_tilemapRect = sf::IntRect( 16, 0, 16, 16 );
        break;
    case Tile::DIRT:
        m_color       = sf::Color(155, 118, 83);
        m_tilemapRect = sf::IntRect(64, 96, 32, 32);
        // m_tilemapRect = sf::IntRect( 32, 0, 16, 16 );
        break;
    case Tile::GRASS:
        m_color       = sf::Color(76, 145, 65);
        m_tilemapRect = sf::IntRect(96, 96, 32, 32);
        // m_tilemapRect = sf::IntRect( 0, 0, 16, 16 );
        break;
    default:
        m_color       = sf::Color::Magenta;
        m_tilemapRect = sf::IntRect(32, 32, 32, 32);
        break;
    }
}


Tile::~Tile()
{
}

void Tile::create()
{
    //? ???
}

void Tile::destroy()
{
    // apply for deletition
}

void Tile::tileUpdate()
{
    if(m_damage > m_damageLimit) {
        destroy();
    }
}

void Tile::provide(sf::Color& color, sf::IntRect& rect)
{
    color = m_color;
    rect  = m_tilemapRect;
}

void Tile::setLightSource(sf::Uint8 lightValue)
{
    m_lightSource = lightValue;
    lightUpdate(lightValue);
}

void Tile::lightUpdate(sf::Uint8 lightValue)
{
    // if received light is lower than current, do nothing and return
    if(lightValue <= m_lightLevel) {
        return;
    }
    // set new light level
    m_lightLevel = lightValue;
    // if there is still light to be transferred after decay, call neighbours
    // lightupdate too
    if(m_lightLevel > m_lightDecay) {
        sf::Uint8 lightTransferred = m_lightLevel - m_lightDecay;
        m_parentMap->tile(m_pos.x + 1, m_pos.y).lightUpdate(lightTransferred);
        m_parentMap->tile(m_pos.x - 1, m_pos.y).lightUpdate(lightTransferred);
        m_parentMap->tile(m_pos.x, m_pos.y + 1).lightUpdate(lightTransferred);
        m_parentMap->tile(m_pos.x, m_pos.y - 1).lightUpdate(lightTransferred);
    }
}

Tile::TileId Tile::getId()
{
    return m_tileId;
}

sf::Vector2i Tile::getPosition()
{
    return m_pos;
}

bool Tile::isSolid()
{
    return m_solid;
}

sf::Uint16 Tile::getDamage()
{
    return m_damage;
}

float Tile::getDamagePercent()
{
    return (float)m_damage / (float)m_damageLimit;
}

void Tile::setDamage(sf::Uint16 newDamage)
{
    m_damage = newDamage;
    tileUpdate();
}

void Tile::setDamagePercent(float damagePercent)
{
    m_damage = static_cast<sf::Uint16>(damagePercent * m_damageLimit);
    tileUpdate();
}

void Tile::applyDamage(sf::Uint16 damage)
{
    m_damage += damage;
}

} //end ns
