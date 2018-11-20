#ifndef LUAPARSER_H
#define LUAPARSER_H


#include <entt/entity/registry.hpp>
#include <sol/sol.hpp>

#include <unordered_map>

namespace ge {

class LuaParser
{
public:
    LuaParser(sol::state& luaState, entt::DefaultRegistry& registry);

    bool parseFile(const std::string& filename, std::unordered_map<std::string, entt::DefaultPrototype>& prototypes);

private:

    sol::state&            m_lua;
    entt::DefaultRegistry& m_registry;
};

} // namespace ge

#endif
