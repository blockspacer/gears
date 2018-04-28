#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"

#include "Cursor.hpp"
#include "system/MovementSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/SelectionSystem.hpp"

#include <anax/World.hpp>

namespace ge {

class World : public anax::World
{
public:
    World();
    ~World();

    void update(float dt);
    void render(sf::RenderTarget& rt);
    void draw(sf::RenderTarget& rt) const;

    void selectionEvent(const sf::Vector2f& pos);
    void commandEvent(const sf::Vector2f& pos);
    void mouseMoveEvent(const sf::Vector2f& pos);

private:
    Map m_map;

    Cursor m_cursor;

    MovementSystem  m_movementSystem;
    RenderingSystem m_renderingSystem;
    SelectionSystem m_selectionSystem;
};

} // end ns

#endif //WORLD_HPP
