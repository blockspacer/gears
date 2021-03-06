#include "LuaParser.hpp"
#include "stdafx.hpp"

#include "world/components/Components.hpp"

namespace ge {

LuaParser::LuaParser(sol::state& luaState, entt::DefaultRegistry& registry)
    : m_lua(luaState), m_registry(registry)
{
}

bool LuaParser::parseFile(const std::string& filename, std::unordered_map<std::string, entt::DefaultPrototype>& prototypes)
{
    m_lua.script_file(filename);

    sol::optional<sol::table> data = m_lua["prototypes"];
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
        std::cout << id << std::endl;

        // TYPE
        std::string type = table["type"];
        if(type == "unit") {
            p.set<cmp::Unit>();
        } else if(type == "item") {
            p.set<cmp::Item>();
        } // TODO ...

        // populate prototype
        for(auto key_value_pair : table) {
            const sol::object& key   = key_value_pair.first;
            const sol::object& value = key_value_pair.second;

            switch(entt::HashedString(key.as<std::string>().c_str())) {

            case "name"_hs:
                p.set<cmp::Name>(value.as<std::string>());
                break;

            case "body"_hs:
                p.set<cmp::Body>(value.as<sol::table>()["w"], value.as<sol::table>()["h"]);
                break;

            case "texture"_hs:
                p.set<cmp::Sprite>(value.as<std::string>());
                break;

            case "maxHealth"_hs:
                p.set<cmp::Health>(value.as<int>());
                break;

            case "selectable"_hs:
                if(value.as<bool>())
                    p.set<cmp::Selectable>();
                break;

            default:
                // INVALID PROPERTY
                break;
            }
        }

        prototypes.insert(std::make_pair(id, std::move(p)));
    }
}

} // namespace ge
