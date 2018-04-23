#ifndef DECLARATIONS_HPP
#define DECLARATIONS_HPP

#include <Thor/Input.hpp>

namespace ge {

enum Direction
{
    NONE = -1,
    UP   = 0x0,
    DOWN,
    LEFT,
    RIGHT,
    UPLEFT,
    UPRIGHT,
    DOWNLEFT,
    DOWNRIGHT
};

enum Orientation
{
    HORIZONTAL,
    VERTICAL
};

// HOTKEYS

enum HotkeyId
{
    HK_UP,
    HK_DOWN,
    HK_LEFT,
    HK_RIGHT,
    HK_ZOOM_IN,
    HK_ZOOM_OUT,

    HK_DIG,
    HK_BUILD,

    HK_MAKE_GROUP_1,
    HK_MAKE_GROUP_2,
    HK_MAKE_GROUP_3,
    HK_MAKE_GROUP_4,
    HK_MAKE_GROUP_5,
    HK_MAKE_GROUP_6,
    HK_MAKE_GROUP_7,
    HK_MAKE_GROUP_8,
    HK_MAKE_GROUP_9,
    HK_SELECT_GROUP_1,
    HK_SELECT_GROUP_2,
    HK_SELECT_GROUP_3,
    HK_SELECT_GROUP_4,
    HK_SELECT_GROUP_5,
    HK_SELECT_GROUP_6,
    HK_SELECT_GROUP_7,
    HK_SELECT_GROUP_8,
    HK_SELECT_GROUP_9,

    // etc...

    HK_COUNT // keep HK_COUNT at the last place
};
}
#endif // !DECLARATIONS_HPP
