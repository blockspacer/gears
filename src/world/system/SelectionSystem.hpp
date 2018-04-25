

#include "world/components/BasicComponents.hpp"
#include "misc/conversions.hpp"

#include <anax/System.hpp>


struct SelectionSystem
    : anax::System<anax::Requires<cmp::Selectable, cmp::Position, cmp::Body>>
{
    void select(sf::FloatRect selectionRect)
    {
        auto entities = getEntities();
        for(auto entity : entities) {
            // Get the needed components
            auto& posComp  = entity.getComponent<cmp::Position>();
            auto& bodyComp = entity.getComponent<cmp::Body>();

            // Calculate Body rectangle
            auto bodyRect = sf::FloatRect(posComp.vec, ge::toVec2f(bodyComp.size));
            if(selectionRect.intersects(bodyRect) || bodyRect.contains(selectionRect.left, selectionRect.top)) {
                entity.addComponent<cmp::Selected>();
            } else {
                entity.removeComponent<cmp::Selected>();
            }
        }
    }
};
