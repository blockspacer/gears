#ifndef LUAPARSER_H
#define LUAPARSER_H


#include <entt/entity/registry.hpp>
#include <sol/sol.hpp>

namespace ge {

class LuaParser
{
public:
    LuaParser(sol::state& luaState, entt::DefaultRegistry& registry);

    bool ParseFile(std::string filename);

private:
    sol::state&            m_lua;
    entt::DefaultRegistry& m_registry;
};

} // namespace ge

#endif
