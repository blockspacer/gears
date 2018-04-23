#pragma once

#include "Hotkey.hpp"
#include "declarations.hpp"

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
    MouseSelectDrag,
    MouseCommand,
    MousePan,
    MouseScroll
};

typedef thor::ActionContext<act::Id> Context;
}

namespace ge {

class ActionHandler
{
public:
    ActionHandler();
    ~ActionHandler();

    thor::ActionMap<act::Id>&                 map();
    thor::ActionMap<act::Id>::CallbackSystem& system();

private:
    void updateHotkey(ge::HotkeyId id, ge::HotkeyPair keys);

    thor::ActionMap<ge::HotkeyId> m_keyMap;
    std::set<ge::HotkeyId>        m_holdableKeys;

    thor::ActionMap<act::Id>                 m_actions;
    thor::ActionMap<act::Id>::CallbackSystem m_events;
};

} // end namespace: ge
