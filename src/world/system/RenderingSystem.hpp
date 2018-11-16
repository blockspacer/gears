#pragma once

#include "world/components/BasicComponents.hpp"

#include <entt/entity/registry.hpp>

class RenderingSystem
{
public:
    RenderingSystem(entt::DefaultRegistry& parentRegistry);

    void draw(sf::RenderTarget& rt) const;

private:
    entt::DefaultRegistry& m_registry;

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
};
