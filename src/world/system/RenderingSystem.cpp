#include "stdafx.hpp"

#include "RenderingSystem.hpp"

RenderingSystem::Renderables RenderingSystem::s_renderables = RenderingSystem::Renderables();

const float RenderingSystem::c_healthBarOffset = 2.f;
const float RenderingSystem::c_healthBarHeight = 2.f;

RenderingSystem::Renderables::Renderables()
{
    selectionBox.setFillColor(sf::Color::Transparent);
    selectionBox.setOutlineColor(sf::Color::Green);
    selectionBox.setOutlineThickness(.5f);

    healthBar.setFillColor(sf::Color::Black);
    healthBar.setOutlineColor(sf::Color::White);
    healthBar.setOutlineThickness(.5f);

    health.setFillColor(sf::Color::Green);
    health.setOutlineColor(sf::Color::Transparent);
}

RenderingSystem::RenderingSystem(entt::DefaultRegistry& parentRegistry)
    : m_registry(parentRegistry) {}

void RenderingSystem::draw(sf::RenderTarget& rt) const
{
    //TODO: Separate logic and drawing

    auto view = m_registry.view<cmp::Position, cmp::Sprite>();
    for(auto entity : view) {
        // Get the components needed
        auto const& pos    = view.get<cmp::Position>(entity);
        auto&       sprite = view.get<cmp::Sprite>(entity);

        // Move sprite where it will be drawn
        sprite.sprite.setPosition(pos.vec);

        // Get sprite bounds
        auto const& spriteRect = sprite.sprite.getGlobalBounds();
        auto const  viewRect   = sf::FloatRect(rt.getView().getCenter() - rt.getView().getSize() / 2.f, rt.getView().getSize());

        // Continue only if sprite is on screen
        if(spriteRect.intersects(viewRect)) {
            // Draw sprite
            rt.draw(sprite.sprite);

            if(m_registry.has<cmp::Selected>(entity)) {
                // Draw Selection Box
                auto& selectionBox = s_renderables.selectionBox;
                selectionBox.setPosition(pos.vec);
                selectionBox.setSize(sf::Vector2f(spriteRect.width, spriteRect.height));
                rt.draw(selectionBox);

                if(m_registry.has<cmp::Health>(entity)) {
                    // Draw Health bar frame
                    auto& healthBar = s_renderables.healthBar;
                    healthBar.setPosition(pos.vec + sf::Vector2f(0, spriteRect.height + c_healthBarOffset));
                    healthBar.setSize(sf::Vector2f(spriteRect.width, c_healthBarHeight));
                    rt.draw(healthBar);

                    // Draw Health amount
                    auto& healthCmp = m_registry.get<cmp::Health>(entity);
                    auto& health    = s_renderables.health;
                    health.setPosition(pos.vec + sf::Vector2f(0, spriteRect.height + c_healthBarOffset));
                    health.setSize(sf::Vector2f(spriteRect.width * healthCmp.getRatio(), c_healthBarHeight));
                    rt.draw(health);
                }
            }
        }
    }
}
