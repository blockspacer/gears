#ifndef ITEMCOMPONENTS_HPP
#define ITEMCOMPONENTS_HPP

#include <anax/Entity.hpp>

#include <SFML/System.hpp>

namespace cmp {

struct Item : anax::Component
{
    Item(sf::Uint32 id)
        : itemId(id) {}

    sf::Uint32 itemId;
};

struct Stored : anax::Component
{
    anax::Entity* storage = nullptr;
};

struct Equipped : anax::Component
{
    anax::Entity* owner = nullptr;
};

struct Equippable : anax::Component
{
    sf::Uint8 onSlots;
};

struct Stackable : anax::Component
{
    Stackable(sf::Uint8 amount, sf::Uint8 limit)
        : stackAmount(amount)
        , stackLimit(limit) {}

    sf::Uint8 stackAmount = 1;
    sf::Uint8 stackLimit  = 1;
};

struct Useable : anax::Component
{
    sf::Uint8 useTime;
    sf::Uint8 coolDown;
};

struct Tool : anax::Component
{
    sf::Uint8 toolId;
};

struct Weapon : anax::Component
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
