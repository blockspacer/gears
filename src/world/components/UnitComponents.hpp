#ifndef UNITCOMPONETS_HPP
#define UNITCOMPONETS_HPP

#include <entt/entity/registry.hpp>

namespace cmp {

struct Unit
{
    std::bitset<8> flags;

    entt::DefaultRegistry::entity_type owningPlayer;
};

struct Name
{
    Name(sf::String givenName = "", sf::String familyName = "")
        : given(givenName), family(familyName) {}

    sf::String given;
    sf::String family;
};

struct Equipment : Container
{
    enum slot
    {
        MAIN_HAND,
        OFF_HAND,
        HEAD,
        CHEST,
        BACK,
        HANDS,
        LEGS,
        AMULET
    };
    Equipment()
        : Container(8) {}
};

struct Inventory : Container
{
    Inventory(std::size_t size = 1)
        : Container(size) {}
};

struct Rideable : Container
{
    Rideable(std::size_t size = 1)
        : Container(size) {}
};

struct Riding
{
    entt::DefaultRegistry::entity_type mount;
};

struct Driving
{
    entt::DefaultRegistry::entity_type vehicle;
};

struct AI
{
    //AiScript* script;
};

struct Order
{
    enum OrderId
    {
        MOVE_TO,
        ATTACK_MOVE_TO,
        PICK_UP,
        PUT_DOWN,
        CRAFT
    };

    Order(OrderId id)
        : orderId(id) {}

    OrderId orderId;
};

struct OrderMoveTo : Order
{
    OrderMoveTo(sf::Vector2f targetPosition)
        : Order(MOVE_TO)
        , target(targetPosition)
    {
    }

    sf::Vector2f target;
};

} // end ns

#endif //UNITCOMPONETS_HPP
