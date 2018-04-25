#pragma once

#include "world/components/BasicComponents.hpp"

#include <anax/System.hpp>


struct MovementSystem : anax::System<anax::Requires<cmp::Position, cmp::Velocity>>
{
    void update(float dt) const
    {
        auto entities = getEntities();
        for(auto entity : entities) {
            auto& posComp = entity.getComponent<cmp::Position>();
            auto& velComp = entity.getComponent<cmp::Velocity>();

            posComp.vec += velComp.vec * dt;
        }
    }
};
