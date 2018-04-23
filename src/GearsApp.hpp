#ifndef GEARSAPP_HPP
#define GEARSAPP_HPP

#include "declarations.hpp"
#include "modules/ActionHandler.hpp"
#include "modules/Mouse.hpp"
#include "modules/ViewPort.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/Gui.hpp>

#include <memory>

//#include "Settings/MkSettings.h"
//#include "World/MkWorld.h"


#define theGame GearsApp::instance()

class GearsApp
{
public:
    /// INIT
    void initialize();

    /// INSTANCE
    // function
    static GearsApp& instance();
    // variable
    static std::unique_ptr<GearsApp> s_instance;

    /// RUN
    void run();

protected:
    /// UPDATE
    // main update function
    void update();

    /// RENDER
    // render the current frame
    void render();

    /// UPDATE HELPERS
    // reset current frame variables
    void resetFrame();
    // handle all kinds of events and actions
    void handleEvents();
    // update selection box & select entities
    void updateSelection();

public:
    /// ACTION CALLBACKS

    void onQuit();
    void onResize();

    void onEscape();
    void onEnter();

    void onNav(ge::Direction direction);

    void onMouseMove(const act::Context& context);
    void onMouseSelect(const act::Context& context);
    void onMouseSelectDrag(const act::Context& context);
    void onMouseCommand(const act::Context& context);
    void onMousePan(const act::Context& context);
    void onMouseScroll(const act::Context& context);

    /// MODULE GETTERS

    // get the game window
    sf::RenderWindow& window();
    // get the default view
    ge::ViewPort& view();
    /// get the mouse
    ge::Mouse& mouse();
    // get the settings
    //MkSettings& settings();
    // get the actions
    ge::ActionHandler& actions();
    // get the GUI
    //tgui::Gui& gui();
    // get the World
    //MkWorld& world();

private:
    /// GAME MODULES

    /// Main Window of the application
    std::unique_ptr<sf::RenderWindow> m_window;

    /// The viewport used for displaying the world to the user
    std::unique_ptr<ge::ViewPort> m_viewPort;

    /// Mouse pointer information
    std::unique_ptr<ge::Mouse> m_mouse;

    /// All the settings of the game
    //std::unique_ptr<MkSettings> m_settings;

    /// The Thor based action handler and mapper
    std::unique_ptr<ge::ActionHandler> m_actions;

    /// The GUI based on the TGUI lib
    //std::unique_ptr<tgui::Gui> m_gui;

    /// The world which the game takes place in
    //std::unique_ptr<MkWorld> m_world;

    /// GAME STATE VARIABLES

    /// PER FRAME STATE VARIABLES
    sf::Clock m_frameClock; // clock for keeping track of frame length
    float     m_dt;         // time since last frame

    /// SELECTION
    //bool               m_selecting;         // if selection is being made
    //sf::Vector2f       m_selectionStartPos; // start of dragging selection box
    //sf::Vector2f       m_selectionEndPos;   // end of dragging selection box
    //sf::RectangleShape m_selectionRect;     // rectngle for displaying selection

    // Cursorshade
    //sf::RectangleShape m_cursorShade; // rectangle for highlighing tile under cursor
};

#endif //GEARSAPP_HPP
