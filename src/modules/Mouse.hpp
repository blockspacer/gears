#ifndef MOUSE_HPP
#define MOUSE_HPP

#include <SFML/System.hpp>

namespace ge {

class Mouse
{
public:

    void setPosition(sf::Vector2i position);

    const sf::Vector2i& position() const { return m_position; };
    const sf::Vector2i& delta() const { return m_delta; };
    const sf::Vector2i& tile() const { return m_tile; };

private:
    sf::Vector2i m_position;   // current position of mouse on screen
    sf::Vector2i m_delta; // vector of mouse position change in this frame
    sf::Vector2i m_tile;  // current tile under mouse
};

} // ge namespace
#endif //MOUSE_HPP
