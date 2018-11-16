#include "SelectionSystem.hpp"

#include "stdafx.hpp"


SelectionSystem::SelectionSystem(entt::DefaultRegistry& parentRegistry)
    : m_registry(parentRegistry)
{
    // set selection rectangle properties
    m_renderable.setFillColor(sf::Color::Transparent);
    m_renderable.setOutlineColor(sf::Color::White);
    m_renderable.setOutlineThickness(1);
}

void SelectionSystem::update()
{
    if(m_selecting) {

        // update rect
        m_selectionRect.left   = std::min(m_selectionStartPos.x, m_selectionEndPos.x);
        m_selectionRect.top    = std::min(m_selectionStartPos.y, m_selectionEndPos.y);
        m_selectionRect.width  = std::fabs(m_selectionEndPos.x - m_selectionStartPos.x);
        m_selectionRect.height = std::fabs(m_selectionEndPos.y - m_selectionStartPos.y);

        // select entities
        select(sf::FloatRect(m_selectionRect));

        if(!m_mouseselect) {
            // end selection
            m_selecting = false;
        }

        // update renderable
        m_renderable.setPosition(m_selectionRect.left, m_selectionRect.top);
        m_renderable.setSize(sf::Vector2f(m_selectionRect.width, m_selectionRect.height));
    }

    // reset mouse select state
    m_mouseselect = false;
}

void SelectionSystem::draw(sf::RenderTarget& rt) const
{
    if(m_selecting) {
        rt.draw(m_renderable);
    }
}

void SelectionSystem::selectionEvent(const sf::Vector2f& pos)
{
    m_mouseselect = true;

    if(m_selecting) {
        // continue selection
        m_selectionEndPos = pos;
    } else {
        // start selection
        m_selecting         = true;
        m_selectionStartPos = pos;
        m_selectionEndPos   = m_selectionStartPos;
    }
}

void SelectionSystem::select(sf::FloatRect selectionRect)
{
    // Increment selection rect to make the intersection valid
    if(selectionRect.width == 0)
        selectionRect.width++;
    if(selectionRect.height == 0)
        selectionRect.height++;

    auto view = m_registry.view<cmp::Selectable, cmp::Position, cmp::Body>();
    for(auto entity : view) {
        // Get the needed components
        auto& pos  = view.get<cmp::Position>(entity);
        auto& body = view.get<cmp::Body>(entity);

        // Calculate Body rectangle
        auto bodyRect = sf::FloatRect(pos.vec, ge::toVec2f(body.size));

        if(selectionRect.intersects(bodyRect)) {
            m_registry.accommodate<cmp::Selected>(entity);
        } else {
            m_registry.reset<cmp::Selected>(entity);
        }
    }
}
