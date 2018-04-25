#pragma once

#include "world/components/BasicComponents.hpp"

#include <anax/System.hpp>

struct OrderingSystem : anax::System<anax::Requires<cmp::Selected>>
{

    void orderMoveTo(sf::Vector2f target);
};
