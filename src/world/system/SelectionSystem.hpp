#pragma once

#include "misc/conversions.hpp"
#include "world/components/Components.hpp"

#include <entt/entity/registry.hpp>

class SelectionSystem
{
public:
    SelectionSystem(entt::DefaultRegistry& parentRegistry);

    void update();

    void draw(sf::RenderTarget& rt) const;

    void selectionEvent(const sf::Vector2f& worldPos);

    void select(sf::FloatRect selectionRect);

private:
    entt::DefaultRegistry& m_registry; // parent regitrsy

    bool          m_selecting;         // if a selection is being made
    bool          m_mouseselect;       // if there was mouse selection since last frame
    sf::Vector2f  m_selectionStartPos; // start of dragging selection box
    sf::Vector2f  m_selectionEndPos;   // end of dragging selection box
    sf::FloatRect m_selectionRect;     // rectngle of the selection

    sf::RectangleShape m_renderable; // the shape to draw on screen
};
