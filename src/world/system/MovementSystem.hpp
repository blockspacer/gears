#pragma once

#include "world/components/BasicComponents.hpp"

#include <entt/entity/registry.hpp>

namespace ge {

class MovementSystem
// anax::System<anax::Requires<cmp::Position, cmp::Velocity>>
{
public:
    MovementSystem(entt::DefaultRegistry& parentRegistry)
        : m_registry(parentRegistry)
    {
        m_registry.prepare<cmp::Position, cmp::Velocity>();
    }

    void update(float dt) const
    {
        auto view = m_registry.view<cmp::Position, cmp::Velocity>(entt::persistent_t{});
        for(auto entity : view) {
            auto& pos = view.get<cmp::Position>(entity);
            auto& vel = view.get<cmp::Velocity>(entity);
            pos.vec   = pos.vec + vel.vec * dt;
        }
    }

private:
    entt::DefaultRegistry& m_registry;
};

} // namespace ge
