#pragma once

#include "world/components/BasicComponents.hpp"

#include <anax/System.hpp>

struct RenderingSystem
    : anax::System<anax::Requires<cmp::Position, cmp::Sprite>>
{

    struct Renderables
    {
        sf::RectangleShape selectionBox;
        sf::RectangleShape healthBar;
        sf::RectangleShape health;

        Renderables();
    };

    static Renderables s_renderables;

    static const float c_healthBarOffset;
    static const float c_healthBarHeight;

    void draw(sf::RenderTarget& rt) const;
};
