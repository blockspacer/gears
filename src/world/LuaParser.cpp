#include "LuaParser.hpp"
#include "stdafx.hpp"

#include "world/components/Components.hpp"

namespace ge {

LuaParser::LuaParser(sol::state& luaState, entt::DefaultRegistry& registry)
    : m_lua(luaState), m_registry(registry)
{
}

bool LuaParser::ParseFile(std::string filename)
{
    m_lua.script_file(filename);

    sol::optional<sol::table> data = m_lua["data"];
    if(!data) {
        std::cerr << "Invalid file" << std::endl;
        return false;
    }

    for(auto record : data.value()) {
        // get record
        const auto id    = record.first.as<std::string>();
        const auto table = record.second.as<sol::table>();
        // create prototype for the record
        entt::DefaultPrototype p(m_registry);
        // set record key as Prototype id
        p.set<cmp::Prototype>(id);

        // TYPE
        if(table["type"] == "unit") {
            p.set<cmp::Unit>();
        } else if(table["type"] == "item") {
            p.set<cmp::Item>();
        }// TODO ...

        // populate prototype
        for(auto key_value_pair : table) {
            const sol::object& key   = key_value_pair.first;
            const sol::object& value = key_value_pair.second;
        }
    }



    /*
        p.set<cmp::Body>(16u, 16u);
        p.set<cmp::Sprite>(sprt);
        p.set<cmp::Health>(100u);
        p.set<cmp::Position>();
        p.set<cmp::Velocity>();
        p.set<cmp::Equipment>();
        p.set<cmp::Inventory>(4u);
        p.set<cmp::Selectable>();
        */
}

} // namespace ge
