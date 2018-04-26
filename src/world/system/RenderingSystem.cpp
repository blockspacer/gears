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

void RenderingSystem::render(sf::RenderTarget& rt) const
{
    //TODO: Separate logic and drawing

    auto entities = getEntities();
    for(auto entity : entities) {
        // Get the components needed
        auto const& posCmp    = entity.getComponent<cmp::Position>();
        auto&       spriteCmp = entity.getComponent<cmp::Sprite>();

        // Move sprite where it will be drawn
        spriteCmp.sprite.setPosition(posCmp.vec);

        // Get sprite bounds
        auto const& spriteRect = spriteCmp.sprite.getGlobalBounds();
        auto const  viewRect   = sf::FloatRect(rt.getView().getCenter() - rt.getView().getSize() / 2.f, rt.getView().getSize());

        // Continue only if sprite is on screen
        if(spriteRect.intersects(viewRect)) {
            // Draw sprite
            rt.draw(spriteCmp.sprite);

            if(entity.hasComponent<cmp::Selected>()) {
                // Draw Selection Box
                auto& selectionBox = s_renderables.selectionBox;
                selectionBox.setPosition(posCmp.vec);
                selectionBox.setSize(sf::Vector2f(spriteRect.width, spriteRect.height));
                rt.draw(selectionBox);

                if(entity.hasComponent<cmp::Health>()) {
                    // Draw Health bar frame
                    auto& healthBar = s_renderables.healthBar;
                    healthBar.setPosition(posCmp.vec + sf::Vector2f(0, spriteRect.height + c_healthBarOffset));
                    healthBar.setSize(sf::Vector2f(spriteRect.width, c_healthBarHeight));
                    rt.draw(healthBar);

                    // Draw Health amount
                    auto& healthCmp = entity.getComponent<cmp::Health>();
                    auto& health    = s_renderables.health;
                    health.setPosition(posCmp.vec + sf::Vector2f(0, spriteRect.height + c_healthBarOffset));
                    health.setSize(sf::Vector2f(spriteRect.width * healthCmp.getRatio(), c_healthBarHeight));
                    rt.draw(health);
                }
            }
        }
    }
}
