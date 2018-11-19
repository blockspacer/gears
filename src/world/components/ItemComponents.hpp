#ifndef ITEMCOMPONENTS_HPP
#define ITEMCOMPONENTS_HPP

#include "BasicComponents.hpp"

#include <SFML/System.hpp>

#include <entt/entity/registry.hpp>

namespace cmp {

struct Item
{
    Item(sf::Uint32 id)
        : itemId(id) {}

    sf::Uint32 itemId;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(itemId);
    }
};

struct Stored : SingleReference
{
};

struct Equipped : SingleReference
{
};

struct Equippable
{
    sf::Uint8 onSlots;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(onSlots);
    }
};

struct Stackable
{
    Stackable(sf::Uint8 amount, sf::Uint8 limit)
        : stackAmount(amount)
        , stackLimit(limit) {}

    sf::Uint8 stackAmount = 1;
    sf::Uint8 stackLimit  = 1;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(stackAmount, stackLimit);
    }
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

} // namespace cmp

#endif //ITEMCOMPONENTS_HPP
