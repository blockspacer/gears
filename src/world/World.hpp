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
    sf::String m_worldName;

    Map m_map;

    Cursor m_cursor;

    entt::DefaultRegistry m_registry;

    MovementSystem  m_movementSystem;
    RenderingSystem m_renderingSystem;
    SelectionSystem m_selectionSystem;
};

} // end ns

#endif //WORLD_HPP
