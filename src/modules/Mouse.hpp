#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/System.hpp>

namespace ge {

class Mouse
{
public:

    void reset();

    void update(float dt);

    void moveEvent(sf::Vector2i newPosition);

    const float         speed() const { return m_speed; };
    const bool          moved() const { return m_speed == 0; };
    const sf::Vector2i& position() const { return m_currPos; };
    const sf::Vector2i& delta() const { return m_delta; };

private:
    float        m_speed;    // speed of the mouse pointer
    sf::Vector2i m_currPos; // current position of mouse on screen
    sf::Vector2i m_lastPos;  // position in last frame
    sf::Vector2i m_delta;    // vector of mouse position change in this frame
};

} // ge namespace
#endif //MOUSE_HPP
