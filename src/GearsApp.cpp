#include "GearsApp.hpp"
#include "stdafx.hpp"

#include <Thor/Time.hpp>

#include <iostream>
#include <memory>

using namespace sf;

std::unique_ptr<GearsApp> GearsApp::s_instance = std::make_unique<GearsApp>();

GearsApp& GearsApp::instance() { return *s_instance; }

void GearsApp::initialize()
{
    // Start Init
    std::cout << "Initializing Gears Engine... \n\n";
    thor::StopWatch initTime;
    initTime.start();

    // print Library versions
    std::cout << "Library versions:\n";
    std::cout << "sfml: " << SFML_VERSION_MAJOR << '.' << SFML_VERSION_MINOR << '.' << SFML_VERSION_PATCH << '\n';
    std::cout << "thor: " << THOR_VERSION_MAJOR << '.' << THOR_VERSION_MINOR << '\n';
    std::cout << "tgui: " << TGUI_VERSION_MAJOR << '.' << TGUI_VERSION_MINOR << '.' << TGUI_VERSION_PATCH << '\n';
    std::cout << '\n';

    /// INIT GAME COMPONENTS
    // order is important
    //m_settings = std::make_unique<MkSettings>();
    //m_actions = std::make_unique<MkActionHandler>();
    m_window = std::make_unique<sf::RenderWindow>(VideoMode(800, 600), "Gears");
    //m_world = std::make_unique<MkWorld>();
    m_viewPort = std::make_unique<ViewPort>(toVec2i(m_window->getSize()));
    //m_gui = std::make_unique<tgui::Gui>(m_window);

    // init window properties
    m_window->setView(*m_viewPort.get());
    m_window->setKeyRepeatEnabled(false);
    //m_window->setVerticalSyncEnabled(m_settings->conf.vSync->getValue());

    /*
    TODO: move to own modules

    // set selection rectangle properties
    m_selectionRect.setFillColor(Color::Transparent);
    m_selectionRect.setOutlineColor(Color::White);
    m_selectionRect.setOutlineThickness(1);

    // set cursorshade rect
    m_cursorShade.setFillColor(sf::Color(0, 0xff, 0, 0x64));
    m_cursorShade.setSize(Vector2f(16.f, 16.f));
*/

    // init frame variables
    m_dt = 0;
    resetFrame();

    // initial update
    update();

    std::cout << "Initialization successful (" << initTime.getElapsedTime().asSeconds() << " s)\n";
    // flush buffer
    std::cout << std::endl;
}

/// RUN & UPDATE & RENDER

void GearsApp::run()
{
    while (m_window->isOpen()) {
        // set time since last frame
        m_dt = m_frameClock.getElapsedTime().asSeconds();
        m_frameClock.restart();

        // reset window
        m_window->clear();
        m_window->setView(*m_viewPort.get());

        // reset frame state
        resetFrame();

        // poll all events and invoke actions based on them
        handleEvents();

        // update frame based on the cosequenses of actions
        update();

        // render frame
        render();

        // display window
        m_window->display();
    }
}

void GearsApp::update()
{
    /* TODO: move to mouse

    if (m_mouseDelta != Vector2i()) {
        if (m_actions->map().isActive(act::MousePan)) {
            auto viewDelta = m_window->mapPixelToCoords(m_mouseDelta) - m_window->mapPixelToCoords(Vector2i(0, 0));
            m_viewPort->panBy(-viewDelta * 2.f);
        }
    }
    */

    // update the view
    m_viewPort->update();

    /* TODO: move

    // update cursor Shade and mouseTile
    Vector2f mouseWorldPos = m_window->mapPixelToCoords(m_mousePos);

    m_mouseTile.x = (static_cast<int>(mouseWorldPos.x) / 16) - (mouseWorldPos.x < 0 ? 1 : 0);
    m_mouseTile.y = (static_cast<int>(mouseWorldPos.y) / 16) - (mouseWorldPos.y < 0 ? 1 : 0);
    m_cursorShade.setPosition(Vector2f(m_mouseTile.x * 16.f, m_mouseTile.y * 16.f));
    */

    // update the world
    //m_world->update(m_dt);

    //TODO: move
    //updateSelection();
}

void GearsApp::render()
{
    // render the world
    //m_world->draw(m_window);

    /* TODO: move

    m_window->draw(m_cursorShade);
    if (m_selecting) {
        m_window->draw(m_selectionRect);
    }
    */
}

void GearsApp::resetFrame()
{
    /*
    // reset per frame member variables
    m_mouseDelta = Vector2i();

    // clear events from last frame
    m_actions->map().clearEvents();
    */
}

void GearsApp::handleEvents()
{
    /*
    // poll the sfml event queue
    Event event;
    while (m_window->pollEvent(event)) {
        // give event to the gui first
        if (!m_gui->handleEvent(event)) {
            // if event falls through gui forward to the Thor ActionMap
            m_actions->map().pushEvent(event);
        }
    }

    // invoke Thor Actions
    m_actions->map().invokeCallbacks(m_actions->system(), &m_window);
    */
}
/*
void GearsApp::updateSelection()
{
    bool rectChanged = false; // rect update required?

    if (m_actions->map().isActive(act::MouseSelect)) {
        if (m_selecting) {
            // continue selection
            m_selectionEndPos = m_window->mapPixelToCoords(m_mousePos);
        } else {
            // start selection
            m_selecting = true;
            m_selectionStartPos = m_window->mapPixelToCoords(m_mousePos);
            m_selectionEndPos = m_selectionStartPos;
        }
        rectChanged = true;
    } else if (m_selecting) {
        // end selection
        m_selecting = false;
        m_selectionStartPos = sf::Vector2f();
        m_selectionEndPos = sf::Vector2f();
        rectChanged = true;

        m_world->selectionEvent(sf::FloatRect(m_selectionRect.getPosition(),
            m_selectionRect.getSize()));
    }

    if (rectChanged) {
        // update rect
        m_selectionRect.setSize(
            sf::Vector2f(std::abs(m_selectionEndPos.x - m_selectionStartPos.x),
                std::abs(m_selectionEndPos.y - m_selectionStartPos.y)));
        m_selectionRect.setPosition(
            sf::Vector2f(std::min(m_selectionStartPos.x, m_selectionEndPos.x),
                std::min(m_selectionStartPos.y, m_selectionEndPos.y)));
    }
}
*/

/// ACTION CALLBACKS
/*
void GearsApp::onQuit() { m_window->close(); }

void GearsApp::onResize() { m_viewPort->resize(toVec2i(m_window->getSize())); }

void GearsApp::onEscape()
{
    onQuit();
    // TODO: open main menu / close others
}

void GearsApp::onEnter()
{
    // TODO: implement
}

void GearsApp::onNav(mk::Direction direction)
{
    // panning by the keyboard

    const float panScale = m_dt * m_viewPort->getZoomFactor() * theGame.settings().conf.panSpeed->getValue();

    sf::Vector2f viewDelta(0, 0);
    switch (direction) {
    case mk::LEFT:
        viewDelta.x -= panScale;
        break;
    case mk::RIGHT:
        viewDelta.x += panScale;
        break;
    case mk::UP:
        viewDelta.y -= panScale;
        break;
    case mk::DOWN:
        viewDelta.y += panScale;
        break;
    default:
        break;
    }
    m_viewPort->panBy(viewDelta);
}

void GearsApp::onMouseMove(const act::Context& context)
{
    Vector2i newMousePos(context.event->mouseMove.x, context.event->mouseMove.y);
    m_mouseDelta = newMousePos - m_mousePos;
    m_mousePos = newMousePos;
}

void GearsApp::onMouseScroll(const act::Context& context)
{
    m_viewPort->zoom(context.event->mouseWheelScroll.delta < 0 ? ViewPort::ZOOM_OUT
                                                           : ViewPort::ZOOM_IN);
}
*/
sf::RenderWindow& GearsApp::window() { return *m_window.get(); }

ViewPort& GearsApp::view() { return *m_viewPort.get(); }

//MkSettings& GearsApp::settings() { return *m_settings.get(); }

//MkActionHandler& GearsApp::actions() { return *m_actions.get(); }

//tgui::Gui& GearsApp::gui() { return *m_gui.get(); }

//MkWorld& GearsApp::world() { return *m_world.get(); }
