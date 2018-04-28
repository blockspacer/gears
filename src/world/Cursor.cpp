#include "stdafx.hpp"

#include "Cursor.hpp"

namespace ge {

Cursor::Cursor()
{
}

void Cursor::update(float dt)
{
    // Animate stuff here
}

void Cursor::draw(sf::RenderTarget& rt) const
{
    rt.draw(m_sprite);
}

void Cursor::setPosition(const sf::Vector2f& newPosition)
{
    m_sprite.setPosition(newPosition);
}

sf::Vector2f Cursor::position() const
{
    return m_sprite.getPosition();
}

} // end namespace
