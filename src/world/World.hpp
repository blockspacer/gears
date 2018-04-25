#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"
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

    void selectionEvent(sf::FloatRect selectionRect);

private:
    Map m_map;

    MovementSystem  m_movementSystem;
    RenderingSystem m_renderingSystem;
    SelectionSystem m_selectionSystem;
};

} // end ns

#endif //WORLD_HPP
