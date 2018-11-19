#ifndef UNITCOMPONETS_HPP
#define UNITCOMPONETS_HPP

#include "BasicComponents.hpp"

#include <entt/entity/registry.hpp>

#include <cereal/types/bitset.hpp>
#include <cereal/types/string.hpp>

namespace cmp {

struct Unit
{
    std::bitset<8> flags;

    entt::DefaultRegistry::entity_type owningPlayer;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(flags, owningPlayer);
    }
};

struct Health
{
    Health(sf::Uint32 health = 1)
        : max(health), current(health) {}

    Health(sf::Uint32 maxHealth, sf::Uint32 currentHealth)
        : max(maxHealth), current(currentHealth) {}

    sf::Uint32 max;
    sf::Uint32 current;

    float getRatio() { return static_cast<float>(current) / static_cast<float>(max); };

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(max, current);
    }
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

struct Riding : SingleReference
{
};

struct Driving : SingleReference
{
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

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(orderId);
    }
};

struct OrderMoveTo : Order
{
    OrderMoveTo(sf::Vector2f targetPosition)
        : Order(MOVE_TO)
        , target(targetPosition)
    {
    }

    sf::Vector2f target;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(orderId, target.x, target.y);
    }
};

} // namespace cmp

#endif //UNITCOMPONETS_HPP
