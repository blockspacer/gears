#include "Mouse.hpp"
#include "stdafx.hpp"


void ge::Mouse::setPosition(sf::Vector2i position)
{
    m_delta    = position - m_position;
    m_position = position;
}
