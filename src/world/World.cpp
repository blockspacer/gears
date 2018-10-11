#include "stdafx.hpp"

#include "World.hpp"

#include "components/BasicComponents.hpp"
#include "components/UnitComponents.hpp"

#include <random>

namespace ge {

World::World()
    : m_map()
{
    addSystem(m_movementSystem);
    addSystem(m_renderingSystem);
    addSystem(m_selectionSystem);

#define TESTING

#ifdef TESTING

    // test dwarf entity
    static auto tex = sf::Texture();
    tex.loadFromFile("res/img/DwarvenKing.png");
    static auto sprt = sf::Sprite(tex);
    sprt.scale(.5f, .5f);

    for(int i = 0; i < 10000; ++i) {

        auto e = createEntity();
        e.addComponent<cmp::Unit>();
        e.addComponent<cmp::Body>(16u, 16u);
        e.addComponent<cmp::Sprite>(sprt);
        e.addComponent<cmp::Health>(100u, std::rand() % 100 + 1);
        e.addComponent<cmp::Position>(std::rand() % (200 * 16) - 100 * 16, std::rand() % (200 * 16) - 100 * 16);
        e.addComponent<cmp::Velocity>(std::rand() % 4 - 2, std::rand() % 4 - 2);
        e.addComponent<cmp::Equipment>();
        e.addComponent<cmp::Inventory>(4u);
        e.addComponent<cmp::Selectable>();
        e.activate();
    }

#endif
}

World::~World()
{
    anax::World::clear();
}

void World::update(float dt)
{
    // Update everything in the correct order

    m_map.update(dt); // The map and its tiles

    anax::World::refresh(); // The entities of the world

    m_movementSystem.update(dt); // How the entities move

    m_selectionSystem.update(); // Select the entities
}

void World::render(sf::RenderTarget& rt)
{
    // Render everything to prepare drawing

    m_map.render(rt); // render (pre-draw) the map

}


void World::draw(sf::RenderTarget& rt) const
{
    // Draw everything on top of each other

    m_map.draw(rt); // The map and its tiles

    m_renderingSystem.draw(rt); //(DRAW) Entities of the world

    m_selectionSystem.draw(rt); // Selection box

    m_cursor.draw(rt); // The cursor
}

/// EVENTS

void World::selectionEvent(const sf::Vector2f& pos)
{
    m_selectionSystem.selectionEvent(pos);
}

void World::commandEvent(const sf::Vector2f& pos)
{
    // TODO: Implement
}

void World::mouseMoveEvent(const sf::Vector2f& pos)
{
    m_cursor.setPosition(pos);
}

} // end ns
