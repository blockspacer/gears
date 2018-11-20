#include "World.hpp"
#include "stdafx.hpp"

#include "LuaParser.hpp"

#include "components/Components.hpp"


#include <cereal/archives/binary.hpp>

#include <entt/entt.hpp>

#include <fstream>
#include <random>

namespace ge {

World::World()
    : m_lua()
    , m_map()
    , m_registry(entt::DefaultRegistry{})
    , m_movementSystem(m_registry)
    , m_renderingSystem(m_registry)
    , m_selectionSystem(m_registry)
{
    // init lua
    m_lua.open_libraries(sol::lib::base);

    LuaParser parser(m_lua, m_registry);

    parser.parseFile("data/GearsTest/prototypes/units.lua", m_prototypes);

    auto entity = m_prototypes.at("dwarfking").create();
    m_registry.assign<cmp::Position>(entity, 4, 2);
    m_registry.assign<cmp::Velocity>(entity, 0, -3);


#define TESTING

#ifdef TESTING

    for(int i = 0; i < 42000; ++i) {
        auto e = m_prototypes.at("dwarfking").create();

        auto& hpComp = m_registry.get<cmp::Health>(e);
        hpComp.current = std::rand() % hpComp.max + 1;
        m_registry.assign<cmp::Position>(e, std::rand() % (200 * 16) - 100 * 16, std::rand() % (200 * 16) - 100 * 16);
        m_registry.assign<cmp::Velocity>(e, std::rand() % 4 - 2, std::rand() % 4 - 2);
    }


#endif

    loadSprites();

}

World::~World()
{
}

void World::saveTo(const sf::String& fileName)
{
    // output file
    std::ofstream f(fileName, std::ios::out | std::ios::app | std::ios::binary);
    // output archive
    cereal::BinaryOutputArchive output{f};
    // save registry
    m_registry.snapshot().entities(output).destroyed(output).component<cmp::Unit, cmp::Body, cmp::Sprite, cmp::Health, cmp::Position, cmp::Velocity, cmp::Equipment, cmp::Inventory, cmp::Selectable>(output);
}
void World::loadFrom(const sf::String& fileName)
{
    //input file
    std::ifstream f(fileName, std::ios::in | std::ios::binary);
    //input archive
    cereal::BinaryInputArchive input{f};
    // load registry
    m_registry.restore().entities(input).destroyed(input).component<cmp::Unit, cmp::Body, cmp::Sprite, cmp::Health, cmp::Position, cmp::Velocity, cmp::Equipment, cmp::Inventory, cmp::Selectable>(input);
    //load sprites
    loadSprites();
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

void World::loadSprites()
{
    auto spriteView = m_registry.view<cmp::Sprite>(entt::raw_t{});
    for(auto& spriteComp : spriteView) {
        spriteComp.sprite = sf::Sprite(m_textures.acquire(
            spriteComp.texPath,
            thor::Resources::fromFile<sf::Texture>(spriteComp.texPath),
            thor::Resources::Reuse));
        spriteComp.sprite.scale(.5f, .5f);
    }
}

} // namespace ge
