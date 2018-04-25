#include "stdafx.hpp"

#include "World.hpp"

#include "components/BasicComponents.hpp"
#include "components/UnitComponents.hpp"

namespace ge {

World::World()
    : m_map()
{
    addSystem(m_movementSystem);
    addSystem(m_renderingSystem);
    addSystem(m_selectionSystem);

    // test dwarf entity
    static auto tex = sf::Texture();
    tex.loadFromFile("res/img/DwarvenKing.png");
    static auto sprt = sf::Sprite(tex);
    sprt.scale(.5f, .5f);

    auto e = createEntity();
    e.addComponent<cmp::Unit>();
    e.addComponent<cmp::Body>(16u, 16u);
    e.addComponent<cmp::Sprite>(sprt);
    e.addComponent<cmp::Health>(100u, 66u);
    e.addComponent<cmp::Position>(0.f, 0.f);
    e.addComponent<cmp::Velocity>(0.f, 0.f);
    e.addComponent<cmp::Equipment>();
    e.addComponent<cmp::Inventory>(4u);
    e.addComponent<cmp::Selectable>();
    e.activate();
}

World::~World()
{
}

void World::update(float dt)
{
    m_map.update(dt);

    anax::World::refresh();

    m_movementSystem.update(dt);
}

void World::render(sf::RenderTarget& rt)
{
    m_map.render(rt);
}


void World::draw(sf::RenderTarget& rt) const
{
    m_map.draw(rt);

    m_renderingSystem.render(rt);
}

void World::selectionEvent(sf::FloatRect selectionRect)
{
    m_selectionSystem.select(selectionRect);
}

} // end ns
