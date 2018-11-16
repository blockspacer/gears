#ifndef ITEMCOMPONENTS_HPP
#define ITEMCOMPONENTS_HPP

#include <entt/entity/registry.hpp>

#include <SFML/System.hpp>

namespace cmp {

struct Item
{
    Item(sf::Uint32 id)
        : itemId(id) {}

    sf::Uint32 itemId;
};

struct Stored
{
    entt::DefaultRegistry::entity_type storage;
};

struct Equipped
{
    entt::DefaultRegistry::entity_type owner;
};

struct Equippable
{
    sf::Uint8 onSlots;
};

struct Stackable
{
    Stackable(sf::Uint8 amount, sf::Uint8 limit)
        : stackAmount(amount)
        , stackLimit(limit) {}

    sf::Uint8 stackAmount = 1;
    sf::Uint8 stackLimit  = 1;
};

struct Useable
{
    sf::Uint8 useTime;
    sf::Uint8 coolDown;
};

struct Tool
{
    sf::Uint8 toolId;
};

struct Weapon
{
    sf::Uint16 baseDamage;
    sf::Uint8  damageType;
};

struct MeeleWeapon : Weapon
{
    sf::Uint8 length;
};

struct RangedWeapon : Weapon
{
    sf::Uint8 range;
};

struct MagicWeapon : Weapon
{
    sf::Uint8 manaCost;
};

} // end ns

#endif //ITEMCOMPONENTS_HPP
