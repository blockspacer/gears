#ifndef TEXTCONVERT_HPP
#define TEXTCONVERT_HPP

#include "core/details/Hotkey.hpp"

#include <SFML/Window.hpp>

#include <sstream>
#include <string>

namespace ge {

inline void stripSpaces(std::string& str)
{
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
}

inline std::string strippedSpaces(std::string str)
{
    stripSpaces(str);
    return str;
}

/// CONVERSIONS FROM STRING

template <typename T>
inline T strToType(const std::string& input)
{
    throw "Unsupported type supplied, either change types, or write a correct conversion function for the template type.";
}

template <>
inline std::string strToType<std::string>(const std::string& input)
{
    return input;
}

template <>
inline bool strToType<bool>(const std::string& input)
{
    return input == "TRUE" ? true : false;
}

template <>
inline int strToType<int>(const std::string& input)
{
    return std::stoi(input);
}

template <>
inline float strToType<float>(const std::string& input)
{
    return std::stof(input);
}

template <>
inline sf::VideoMode strToType<sf::VideoMode>(const std::string& input)
{
    sf::VideoMode     value;
    std::stringstream ss(ge::strippedSpaces(input));
    std::string       str;
    // get parts of the stream split by 'x' until it ends
    int id = 0;
    while(std::getline(ss, str, 'x') && id < 3) {
        switch(id++) {
        case 0:
            value.width = strToType<int>(str);
            break;
        case 1:
            value.height = strToType<int>(str);
            break;
        case 2:
            value.bitsPerPixel = strToType<int>(str);
            break;
        }
    }
    return value;
}

template <>
inline ge::Hotkey strToType<ge::Hotkey>(const std::string& input)
{
    ge::Hotkey        value;
    std::stringstream ss(ge::strippedSpaces(input));
    std::string       str;

    // get parts of the stream split by '+' until it ends
    while(std::getline(ss, str, '+')) {
        if(str == "ctrl")
            value.ctrl = true;
        else if(str == "shift")
            value.shift = true;
        else if(str == "alt")
            value.alt = true;
        else {
            try // to convert string to char
            {
                value.key = thor::toKeyboardKey(str);
            } catch(const std::exception&) {
                return ge::Hotkey(sf::Keyboard::Unknown);
            }

            // key has been read so we can return
            return value;
        }
    }
    // string ended without valid key
    return ge::Hotkey(sf::Keyboard::Unknown);
}

template <>
inline ge::HotkeyPair strToType<ge::HotkeyPair>(const std::string& input)
{
    ge::HotkeyPair    value;
    std::stringstream ss(input);

    // get first part
    std::string str;
    std::getline(ss, str, ',');
    value.first = strToType<ge::Hotkey>(str);

    // if there is still text in the stream that will be the second part
    if(std::getline(ss, str)) {
        value.second = strToType<ge::Hotkey>(str);
    }

    return value;
}


/// CONVERSIONS TO STRING

template <typename T>
inline std::string typeToStr(T value)
{
    throw "Unsupported type supplied, either change types, or write a correct conversion function for the template type.";
}

template <>
inline std::string typeToStr<std::string>(std::string value)
{
    return value;
}

template <>
inline std::string typeToStr<bool>(bool value)
{
    return (value) ? "TRUE" : "FALSE";
}

template <>
inline std::string typeToStr<int>(int value)
{
    return std::to_string(value);
}

template <>
inline std::string typeToStr<float>(float value)
{
    return std::to_string(value);
}

template <>
inline std::string typeToStr<sf::VideoMode>(sf::VideoMode value)
{
    std::string str;
    str += typeToStr<int>(value.width) + "x";
    str += typeToStr<int>(value.height) + "x";
    str += typeToStr<int>(value.bitsPerPixel);
    return str;
}


template <>
inline std::string typeToStr<ge::Hotkey>(ge::Hotkey value)
{
    std::string str;
    str += value.ctrl ? "ctrl+" : "";
    str += value.shift ? "shift+" : "";
    str += value.alt ? "alt+" : "";
    str += thor::toString(value.key);
    return str;
}

template <>
inline std::string typeToStr<ge::HotkeyPair>(ge::HotkeyPair value)
{
    std::string str;
    if(value.first.key != sf::Keyboard::Unknown) {
        str += ge::typeToStr<ge::Hotkey>(value.first);
    }
    if(value.second.key != sf::Keyboard::Unknown) {
        str += ", " + ge::typeToStr<ge::Hotkey>(value.second);
    }
    return str;
}

} //end ns:ge
#endif
