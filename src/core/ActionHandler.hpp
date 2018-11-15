#pragma once

#include "details/Hotkey.hpp"
#include "misc/declarations.hpp"

#include <Thor/Input.hpp>
#include <set>

namespace act {
enum Id
{
    Enter,
    Escape,

    Resize,
    Quit,

    NavLeft,
    NavRight,
    NavUp,
    NavDown,

    MouseMove,
    MouseSelect,
    MouseCommand,
    MousePan,
    MouseScroll
};

typedef thor::ActionContext<act::Id> Context;
} // namespace act

namespace ge {

class GearsEngine;

class ActionHandler
{
public:
    ActionHandler();
    ~ActionHandler();

    void clearEvents();
    void pushEvent(const sf::Event& event);

    void invokeCallbacks(sf::Window* window);

private:
    void updateHotkey(ge::HotkeyId id, ge::HotkeyPair keys);

    thor::ActionMap<ge::HotkeyId> m_keyMap;
    std::set<ge::HotkeyId>        m_holdableKeys;

    thor::ActionMap<act::Id>                 m_actions;
    thor::ActionMap<act::Id>::CallbackSystem m_events;
};

} // namespace ge
