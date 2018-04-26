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
    m_map.update(dt);

    anax::World::refresh();

    m_movementSystem.update(dt);

    m_selectionSystem.update();
}

void World::render(sf::RenderTarget& rt)
{
    m_map.render(rt);
}


void World::draw(sf::RenderTarget& rt) const
{
    m_map.draw(rt);

    m_renderingSystem.render(rt);

    m_selectionSystem.draw(rt);
}

void World::selectionEvent(const sf::Vector2f& pos)
{
    m_selectionSystem.selectionEvent(pos);
}

void World::commandEvent(const sf::Vector2f& pos)
{
    // TODO: Implement
}

} // end ns
