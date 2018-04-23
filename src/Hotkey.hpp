#ifndef HOTKEY_HPP
#define HOTKEY_HPP

#include <Thor/Input.hpp>

namespace ge {

struct Hotkey
{
    Hotkey(sf::Keyboard::Key key   = sf::Keyboard::Unknown,
           bool              ctrl  = false,
           bool              shift = false,
           bool              alt   = false)
        : key(key), ctrl(ctrl), shift(shift), alt(alt){};

    ~Hotkey(){};

    sf::Keyboard::Key key;

    bool ctrl;
    bool shift;
    bool alt;

    thor::Action toAction(thor::Action::ActionType type = thor::Action::Hold)
    {
        thor::Action act(key, type);
        if(ctrl)
            act = act && (thor::Action(sf::Keyboard::LControl) ||
                          thor::Action(sf::Keyboard::RControl));
        if(shift)
            act = act && (thor::Action(sf::Keyboard::LShift) ||
                          thor::Action(sf::Keyboard::RShift));
        if(alt)
            act = act && (thor::Action(sf::Keyboard::LAlt) ||
                          thor::Action(sf::Keyboard::RAlt));
        return act;
    }
};

inline bool operator==(const Hotkey lho, const Hotkey rho)
{
    return lho.key == rho.key &&
           lho.ctrl == rho.ctrl &&
           lho.shift == rho.shift &&
           lho.alt == rho.alt;
}

typedef std::pair<Hotkey, Hotkey> HotkeyPair;
}

inline thor::Action
toAction(ge::HotkeyPair           hkPair,
         thor::Action::ActionType type = thor::Action::Hold)
{
    return hkPair.first.toAction(type) || hkPair.second.toAction(type);
}



#endif // !HOTKEY_HPP
