#include "World.hpp"
#include "stdafx.hpp"

#include "components/BasicComponents.hpp"
#include "components/UnitComponents.hpp"

#include <cereal/archives/binary.hpp>

#include <entt/entt.hpp>

#include <fstream>
#include <random>

namespace ge {

World::World()
    : m_map()
    , m_registry(entt::DefaultRegistry{})
    , m_movementSystem(m_registry)
    , m_renderingSystem(m_registry)
    , m_selectionSystem(m_registry)
{

#define TESTING

#ifdef TESTING

    // test dwarf entity
    static auto tex = sf::Texture();
    tex.loadFromFile("res/img/DwarvenKing.png");
    static auto sprt = sf::Sprite(tex);
    sprt.scale(.5f, .5f);

    entt::DefaultPrototype p(m_registry);
    p.set<cmp::Unit>();
    p.set<cmp::Body>(16u, 16u);
    p.set<cmp::Sprite>(sprt);
    p.set<cmp::Health>(100u);
    p.set<cmp::Position>();
    p.set<cmp::Velocity>();
    p.set<cmp::Equipment>();
    p.set<cmp::Inventory>(4u);
    p.set<cmp::Selectable>();

    for(int i = 0; i < 100000; ++i) {
        auto e = p.create();
        m_registry.replace<cmp::Health>(e, 100u, std::rand() % 100 + 1);
        m_registry.replace<cmp::Position>(e, std::rand() % (200 * 16) - 100 * 16, std::rand() % (200 * 16) - 100 * 16);
        m_registry.replace<cmp::Velocity>(e, std::rand() % 4 - 2, std::rand() % 4 - 2);
    }

#endif
}

World::~World()
{
}

void World::saveTo(const sf::String& fileName)
{
    // output file
    std::ofstream f;

    /*
    //open file for text output
    f.open(fileName, std::ios::out | std::ios::trunc);
    f << m_worldName.toAnsiString() << std::endl;
    // TODO: savefile version
    f.close();
    */

    // open file for binary output
    //f.open(fileName, std::ios::out | std::ios::app | std::ios::binary);
    //cereal::BinaryOutputArchive output{f};
    //m_registry.snapshot().entities(output).destroyed(output).component<cmp::Unit, cmp::Body, cmp::Sprite, cmp::Health, cmp::Position, cmp::Velocity, cmp::Equipment, cmp::Inventory, cmp::Selectable>(output);
}
void World::loadFrom(const sf::String& fileName)
{
    std::ifstream f;

    /*
    f.open(fileName);
    std::string str;
    std::getline(f, str);
    m_worldName = str;
    f.close()
    */

    //f.open(fileName, std::ios::binary);
    //cereal::BinaryInputArchive input{f};
    //m_registry.snapshot().entities(input).destroyed(input).component<cmp::Unit, cmp::Body, cmp::Sprite, cmp::Health, cmp::Position, cmp::Velocity, cmp::Equipment, cmp::Inventory, cmp::Selectable>(input);
}

void World::update(float dt)
{
    // Update everything in the correct order

    m_map.update(dt); // The map and its tiles

    m_movementSystem.update(dt); // How the entities move

    m_selectionSystem.update(); // Select the entities

    m_cursor.update(dt);
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

} // namespace ge
