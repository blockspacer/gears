#ifndef CURSOR_HPP
#define CURSOR_HPP

#include <SFML/Graphics.hpp>

namespace ge {

class Cursor
{
public:
    Cursor();

    void update(float dt);

    void draw(sf::RenderTarget& rt) const;

    void setPosition(const sf::Vector2f& newPosition);
    sf::Vector2f position() const;

private:
    sf::Sprite m_sprite;

    sf::Vector2i m_tile;
};

} // end namespace

#endif //CURSOR_HPP
