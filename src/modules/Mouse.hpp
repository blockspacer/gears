#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/System.hpp>

namespace ge {

class Mouse
{
public:

    const sf::Vector2i& position() const { return m_mousePos; };
    const sf::Vector2i& delta() const { return m_mouseDelta; };
    const sf::Vector2i& tile() const { return m_mouseTile; };

private:
    sf::Vector2i m_mousePos;   // current position of mouse on screen
    sf::Vector2i m_mouseDelta; // vector of mouse position change in this frame
    sf::Vector2i m_mouseTile;  // current tile under mouse
};

} // ge namespace
#endif //MOUSE_HPP
