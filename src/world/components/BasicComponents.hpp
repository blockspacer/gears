#ifndef BASICCOMPONENTS_HPP
#define BASICCOMPONENTS_HPP

#include <entt/entity/registry.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

namespace cmp {

struct Position
{
    Position(sf::Vector2f position = sf::Vector2f(0.f, 0.f))
        : vec(position) {}

    Position(float x, float y)
        : vec(x, y) {}

    sf::Vector2f vec;
};

struct Velocity
{
    Velocity(sf::Vector2f velocity = sf::Vector2f(0.f, 0.f))
        : vec(velocity) {}

    Velocity(float x, float y)
        : vec(x, y) {}

    sf::Vector2f vec;
};

struct Body
{
    Body(sf::Vector2u bodySize = sf::Vector2u(0, 0))
        : size(bodySize) {}

    Body(std::size_t x, std::size_t y)
        : size(x, y) {}

    sf::Vector2u size;
};

struct Sprite
{
    Sprite(const sf::Sprite& sprite = sf::Sprite())
        : sprite(sprite) {}

    sf::Sprite sprite;
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
};

struct Selectable
{
};

struct Selected
{
};

struct Container
{
    Container(std::size_t size = 1)
    {
        setSize(size);
    }

    void setSize(std::size_t size)
    {
        if(size > contents.size()) {
            contents.reserve(size);
            contents.resize(size);
        } else if(size < contents.size()) {
            contents.resize(size);
            contents.shrink_to_fit();
        }
    }

    std::vector<entt::DefaultRegistry::entity_type> contents;
};

} // namespace cmp

#endif //BASICCOMPONENTS_HPP
