#include "GearsEngine.hpp"
#include "stdafx.hpp"

#include <Thor/Time.hpp>

#include <iostream>
#include <memory>

using namespace sf;

std::unique_ptr<GearsEngine> GearsEngine::s_instance = std::make_unique<GearsEngine>();

GearsEngine& GearsEngine::instance() { return *s_instance; }

void GearsEngine::initialize()
{
    // Start Init timer
    sf::Clock initClock;

    std::cout << "Initializing Gears Engine... \n\n";

    // print Library versions
    std::cout << "Library versions:\n";
    std::cout << "sfml: " << SFML_VERSION_MAJOR << '.' << SFML_VERSION_MINOR << '.' << SFML_VERSION_PATCH << '\n';
    std::cout << "thor: " << THOR_VERSION_MAJOR << '.' << THOR_VERSION_MINOR << '\n';
    std::cout << "tgui: " << TGUI_VERSION_MAJOR << '.' << TGUI_VERSION_MINOR << '.' << TGUI_VERSION_PATCH << '\n';
    std::cout << '\n';

    /// INIT GAME COMPONENTS
    // order is important
    m_settings = std::make_unique<ge::Settings>();
    m_actions  = std::make_unique<ge::ActionHandler>();
    m_window   = std::make_unique<sf::RenderWindow>(VideoMode(800, 600), "Gears");
    m_viewPort = std::make_unique<ge::ViewPort>(ge::toVec2i(m_window->getSize()));
    m_mouse    = std::make_unique<ge::Mouse>();
    m_gui      = std::make_unique<tgui::Gui>(*m_window);
    m_world    = std::make_unique<ge::World>();

    // init window properties
    m_window->setKeyRepeatEnabled(false);
    m_window->setVerticalSyncEnabled(m_settings->conf.vSync->getValue());

    /*
    TODO: move to own modules

    // set cursorshade rect
    m_cursorShade.setFillColor(sf::Color(0, 0xff, 0, 0x64));
    m_cursorShade.setSize(Vector2f(16.f, 16.f));
*/

    // make an initial loop with 0 dt
    m_dt = 0;
    loop();

    std::cout << "Initialization successful (" << initClock.getElapsedTime().asSeconds() << " s)\n";
    std::cout << std::flush;
}

/// RUN CYCLE

void GearsEngine::run()
{
    while(m_window->isOpen()) {

        // measure time since last frame & restart clock
        m_dt = m_frameClock.getElapsedTime().asSeconds();
        m_frameClock.restart();

        // call main loop
        loop();
    }
}

void GearsEngine::loop()
{
    // reset frame state
    resetFrame();

    // poll all events and invoke actions based on them
    handleEvents();

    // update frame based on the cosequenses of actions
    update();

    // render frame
    render();

    // draw everything
    draw();
}

void GearsEngine::resetFrame()
{
    // reset window
    m_window->clear();
    m_window->setView(*m_viewPort.get());

    // reset mouse delta
    m_mouse->reset();

    // clear events from last frame
    m_actions->map().clearEvents();
}

void GearsEngine::handleEvents()
{
    // poll the sfml event queue
    Event event;
    while(m_window->pollEvent(event)) {
        // give event to the gui first
        if(!m_gui->handleEvent(event)) {
            // if event falls through gui forward to the Thor ActionMap
            m_actions->map().pushEvent(event);
        }
    }

    // invoke Thor Actions
    m_actions->map().invokeCallbacks(m_actions->system(), m_window.get());
}

void GearsEngine::update()
{
    // update the view
    m_viewPort->update();

    m_mouse->update(m_dt);

    /* TODO: move
    // update cursor Shade and mouseTile
    Vector2f mouseWorldPos = m_window->mapPixelToCoords(m_mousePos);
    m_mouseTile.x = (static_cast<int>(mouseWorldPos.x) / 16) - (mouseWorldPos.x < 0 ? 1 : 0);
    m_mouseTile.y = (static_cast<int>(mouseWorldPos.y) / 16) - (mouseWorldPos.y < 0 ? 1 : 0);
    m_cursorShade.setPosition(Vector2f(m_mouseTile.x * 16.f, m_mouseTile.y * 16.f));
    */

    // update the world
    m_world->update(m_dt);
}

void GearsEngine::render()
{
    m_world->render(*m_window);
}

void GearsEngine::draw()
{
    // draw the world
    m_world->draw(*m_window);

    /* TODO: move
    m_window->draw(m_cursorShade);
    */

    // display window
    m_window->display();
}



/// ACTION CALLBACKS

void GearsEngine::onQuit()
{
    m_window->close();
}

void GearsEngine::onResize()
{
    m_viewPort->resize(ge::toVec2i(m_window->getSize()));
}

void GearsEngine::onEscape()
{
    onQuit();
    // TODO: open main menu / close others
}

void GearsEngine::onEnter()
{
    // TODO: implement
}

void GearsEngine::onNav(ge::Direction direction)
{
    // panning by the keyboard

    // TODO: When in menu, navigate buttons instead

    const float panScale = m_dt * m_viewPort->getZoomFactor() * m_settings->conf.panSpeed->getValue();

    sf::Vector2f viewDelta(0, 0);
    switch(direction) {
    case ge::LEFT:
        viewDelta.x -= panScale;
        break;
    case ge::RIGHT:
        viewDelta.x += panScale;
        break;
    case ge::UP:
        viewDelta.y -= panScale;
        break;
    case ge::DOWN:
        viewDelta.y += panScale;
        break;
    default:
        break;
    }
    m_viewPort->panBy(viewDelta);
}

void GearsEngine::onMouseMove(const act::Context& context)
{
    m_mouse->moveEvent(sf::Vector2i(context.event->mouseMove.x, context.event->mouseMove.y));

    m_world->mouseMoveEvent(m_window->mapPixelToCoords(m_mouse->position()));
}

void GearsEngine::onMouseSelect(const act::Context& context)
{
    m_world->selectionEvent(m_window->mapPixelToCoords(m_mouse->position()));
}

void GearsEngine::onMouseCommand(const act::Context& context)
{
    m_world->commandEvent(m_window->mapPixelToCoords(m_mouse->position()));
}

void GearsEngine::onMousePan(const act::Context& context)
{
    auto viewDelta = m_window->mapPixelToCoords(m_mouse->delta()) -
                     m_window->mapPixelToCoords(Vector2i(0, 0));
    m_viewPort->panBy(-viewDelta);
}

void GearsEngine::onMouseScroll(const act::Context& context)
{
    m_viewPort->zoom(context.event->mouseWheelScroll.delta < 0 ? ge::ZOOM_OUT : ge::ZOOM_IN);
}
