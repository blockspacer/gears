#ifndef CONVERSIONS_HPP
#define CONVERSIONS_HPP

#include <SFML/System/Vector2.hpp>

#include <algorithm>

template <typename T>
inline sf::Vector2f toVec2f( sf::Vector2<T> vector )
{
  return sf::Vector2f( static_cast<float>( vector.x ),
                       static_cast<float>( vector.y ) );
}

template <typename T>
inline sf::Vector2i toVec2i( sf::Vector2<T> vector )
{
  return sf::Vector2i( static_cast<int>( vector.x ),
                       static_cast<int>( vector.y ) );
}

template <typename T>
inline sf::Vector2u toVec2u( sf::Vector2<T> vector )
{
  return sf::Vector2u( static_cast<unsigned int>( vector.x ),
                       static_cast<unsigned int>( vector.y ) );
}

template <typename T>
inline T manhattanDist( sf::Vector2<T> vector1, sf::Vector2<T> vector2 )
{
  return abs( vector2.x - vector1.x ) + abs( vector2.y - vector1.y );
}

template <typename T>
inline T clamp( T value, T low, T high )
{
  return ( high < low ) ? value : std::max( low, std::min( high, value ) );
}


#endif // CONVERSIONS_HPP
