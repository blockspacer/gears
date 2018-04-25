#ifndef UNITCOMPONETS_HPP
#define UNITCOMPONETS_HPP

#include "BasicComponents.hpp"

namespace cmp {

struct Unit : anax::Component
{
    std::bitset<8> flags;

    anax::Entity* owner;
};

struct Name : anax::Component
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
    Inventory(size_t size = 1)
        : Container(size) {}
};

struct Rideable : Container
{
    Rideable(size_t size = 1)
        : Container(size) {}
};

struct Riding : anax::Component
{
    anax::Entity* mount = nullptr;
};

struct Driving : anax::Component
{
    anax::Entity* vehicle = nullptr;
};

struct AI : anax::Component
{
    //AiScript* script;
};

struct Order : anax::Component
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
