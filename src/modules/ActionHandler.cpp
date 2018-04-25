#include "ActionHandler.hpp"
#include "GearsEngine.hpp"
#include "misc/conversions.hpp"
#include "stdafx.hpp"

namespace ge {

using namespace sf;
using namespace thor;

ActionHandler::ActionHandler()
{
    /// BASIC EVENTS

    // Quit
    m_actions[act::Quit] = Action(Event::Closed);
    m_events.connect0(act::Quit, std::bind(&GearsEngine::onQuit, std::ref(theGame)));

    // Resize
    m_actions[act::Resize] = Action(Event::Resized);
    m_events.connect0(act::Resize, std::bind(&GearsEngine::onResize, std::ref(theGame)));

    /// KEY NAVIGATION

    // define keys that can be holded down
    m_holdableKeys.insert(HK_UP);
    m_holdableKeys.insert(HK_DOWN);
    m_holdableKeys.insert(HK_LEFT);
    m_holdableKeys.insert(HK_RIGHT);


    for(int i = 0; i < HK_COUNT; ++i) {
        HotkeyId id = static_cast<HotkeyId>(i);

        updateHotkey(id, theGame.settings().keys.at(id).getBoth());

        theGame.settings().keys.at(id).getProperty().on_change().connect(
            [this, id](HotkeyPair hotkeys) { updateHotkey(id, hotkeys); });
    }


    // Enter / Accept
    m_actions[act::Enter] = Action(Keyboard::Return, Action::ReleaseOnce);
    m_events.connect0(act::Enter, std::bind(&GearsEngine::onEnter, std::ref(theGame)));

    // Escape / Back
    m_actions[act::Escape] = Action(Keyboard::Escape, Action::ReleaseOnce);
    m_events.connect0(act::Escape, std::bind(&GearsEngine::onEscape, std::ref(theGame)));

    // Direction keys
    m_actions[act::NavUp]    = realtimeAction([this]() { return m_keyMap.isActive(ge::HK_UP); });
    m_actions[act::NavDown]  = realtimeAction([this]() { return m_keyMap.isActive(ge::HK_DOWN); });
    m_actions[act::NavLeft]  = realtimeAction([this]() { return m_keyMap.isActive(ge::HK_LEFT); });
    m_actions[act::NavRight] = realtimeAction([this]() { return m_keyMap.isActive(ge::HK_RIGHT); });

    m_events.connect(act::NavUp, std::bind(&GearsEngine::onNav, std::ref(theGame), ge::UP));
    m_events.connect(act::NavDown, std::bind(&GearsEngine::onNav, std::ref(theGame), ge::DOWN));
    m_events.connect(act::NavLeft, std::bind(&GearsEngine::onNav, std::ref(theGame), ge::LEFT));
    m_events.connect(act::NavRight, std::bind(&GearsEngine::onNav, std::ref(theGame), ge::RIGHT));

    /// MOUSE NAVIGATION

    m_actions[act::MouseMove]       = Action(Event::MouseMoved);
    m_actions[act::MouseSelect]     = Action(sf::Mouse::Left);
    m_actions[act::MouseCommand]    = Action(sf::Mouse::Right);
    m_actions[act::MousePan]        = Action(sf::Mouse::Right) && m_actions[act::MouseMove];
    m_actions[act::MouseScroll]     = Action(Event::MouseWheelScrolled);

    m_events.connect(act::MouseMove,
                     [](const act::Context& context) { theGame.onMouseMove(context); });
    m_events.connect(act::MouseSelect,
                     [](const act::Context& context) { theGame.onMouseSelect(context); });
    m_events.connect(act::MouseCommand,
                     [](const act::Context& context) { theGame.onMouseCommand(context); });
    m_events.connect(act::MousePan,
                     [](const act::Context& context) { theGame.onMousePan(context); });
    m_events.connect(act::MouseScroll,
                     [](const act::Context& context) { theGame.onMouseScroll(context); });
}


ActionHandler::~ActionHandler()
{
}

thor::ActionMap<act::Id>& ActionHandler::map()
{
    return m_actions;
}

thor::ActionMap<act::Id>::CallbackSystem& ActionHandler::system()
{
    return m_events;
}

void ActionHandler::updateHotkey(ge::HotkeyId id, ge::HotkeyPair keys)
{
    Action::ActionType type;

    if(m_holdableKeys.find(id) != m_holdableKeys.end())
        type = Action::Hold;
    else
        type = Action::ReleaseOnce;

    m_keyMap[id] = toAction(keys, type);
}

} //end namesapce
