#include "Mouse.hpp"
#include "stdafx.hpp"

#include <cmath>

namespace ge {

void Mouse::reset()
{
    m_lastPos = m_currPos;
    m_delta   = sf::Vector2i();
    m_speed   = 0.f;
}

void Mouse::update(float dt)
{
    // calculate speed
    m_speed = std::sqrt(m_delta.x * m_delta.x + m_delta.y * m_delta.y) / dt;
}

void Mouse::moveEvent(sf::Vector2i newPosition)
{
    // set new position
    m_currPos = newPosition;
    // accumulate delta since last update
    m_delta = m_currPos - m_lastPos;
}

} //end ns
