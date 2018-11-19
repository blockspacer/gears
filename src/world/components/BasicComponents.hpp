#ifndef BASICCOMPONENTS_HPP
#define BASICCOMPONENTS_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <entt/entity/registry.hpp>

#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace cmp {

struct Prototype
{
    Prototype(sf::String id)
        : id(id) {}

    sf::String id;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(id);
    }
};

struct Name
{
    Name(sf::String name, sf::String namePrefix = "", sf::String nameSuffix = "")
        : name(name), prefix(namePrefix), suffix(nameSuffix) {}

    sf::String name;
    sf::String prefix;
    sf::String suffix;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(prefix, name, suffix);
    }
};

struct Position
{
    Position(sf::Vector2f position = sf::Vector2f(0.f, 0.f))
        : vec(position) {}

    Position(float x, float y)
        : vec(x, y) {}

    sf::Vector2f vec;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(vec.x, vec.y);
    }
};

struct Velocity
{
    Velocity(sf::Vector2f velocity = sf::Vector2f(0.f, 0.f))
        : vec(velocity) {}

    Velocity(float x, float y)
        : vec(x, y) {}

    sf::Vector2f vec;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(vec.x, vec.y);
    }
};

struct Body
{
    Body(sf::Vector2u bodySize = sf::Vector2u(0, 0))
        : size(bodySize) {}

    Body(std::size_t x, std::size_t y)
        : size(x, y) {}

    sf::Vector2u size;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(size.x, size.y);
    }
};

struct Sprite
{
    Sprite(const sf::Sprite& sprite = sf::Sprite())
        : sprite(sprite) {}

    sf::String spriteId;
    sf::Sprite sprite;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(spriteId);
    }
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

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(contents);
    }
};

struct SingleReference
{
    SingleReference(entt::DefaultRegistry::entity_type referredEntity)
        : entity(referredEntity) {}

    entt::DefaultRegistry::entity_type entity;

    template <class Archive>
    void serialize(Archive& archive)
    {
        archive(entity);
    }
};

struct Selectable
{
};

struct Selected
{
};

} // namespace cmp

#endif //BASICCOMPONENTS_HPP
