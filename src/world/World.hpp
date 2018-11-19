#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"

#include "Cursor.hpp"
#include "system/MovementSystem.hpp"
#include "system/RenderingSystem.hpp"
#include "system/SelectionSystem.hpp"

#include <entt/entity/registry.hpp>

namespace ge {

class World
{
public:
    World();
    ~World();

    void saveTo(const sf::String& fileName);
    void loadFrom(const sf::String& fileName);

    void update(float dt);
    void render(sf::RenderTarget& rt);
    void draw(sf::RenderTarget& rt) const;

    void selectionEvent(const sf::Vector2f& pos);
    void commandEvent(const sf::Vector2f& pos);
    void mouseMoveEvent(const sf::Vector2f& pos);

private:
    // Gameplay Map
    ge::Map m_map;

    // Graphical cursor
    ge::Cursor m_cursor;

    // Registry of all the entities
    entt::DefaultRegistry m_registry;

    // The lua state
    sol::state m_lua;

    // Systems
    MovementSystem  m_movementSystem;
    RenderingSystem m_renderingSystem;
    SelectionSystem m_selectionSystem;
};

} // end ns

#endif //WORLD_HPP
