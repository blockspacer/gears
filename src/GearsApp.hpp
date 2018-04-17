#ifndef GEARSAPP_HPP
#define GEARSAPP_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include <TGUI/Gui.hpp>

#include "modules/ViewPort.hpp"

//#include "Settings/MkSettings.h"
//#include "System/MkActionHandler.h"
//#include "World/MkWorld.h"

//#include "Declarations.h"

#define theGame GearsApp::instance()

class GearsApp {
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
    /*
  void onQuit();
  void onResize();

  void onEscape();
  void onEnter();

  void onNav(mk::Direction direction);
  void onMouseMove(const act::Context& context);
  void onMouseScroll(const act::Context& context);
*/

    /// REFERENCE GETTERS

    // get the game window
    sf::RenderWindow& window();
    // get the default view
    ViewPort& view();
    // get the settings
    //MkSettings& settings();
    // get the actions
    //MkActionHandler& actions();
    // get the GUI
    //tgui::Gui& gui();
    // get the World
    //MkWorld& world();

private:
    /// GAME MODULES

    /// Main Window of the application
    std::unique_ptr<sf::RenderWindow> m_window;

    /// The viewport used for displaying the world to the user
    std::unique_ptr<ViewPort> m_viewPort;

    /// All the settings of the game
    //std::unique_ptr<MkSettings> m_settings;

    /// The Thor based action handler and mapper
    //std::unique_ptr<MkActionHandler> m_actions;

    /// The GUI based on the TGUI lib
    //std::unique_ptr<tgui::Gui> m_gui;

    /// The world which the game takes place in
    //std::unique_ptr<MkWorld> m_world;

    /// GAME STATE VARIABLES
    //sf::Vector2i m_mousePos;   // current position of mouse on screen
    //sf::Vector2i m_mouseTile;  // current tile under mouse

    /// PER FRAME STATE VARIABLES
    sf::Clock m_frameClock; // clock for keeping track of frame length
    float m_dt; // time since last frame
    //sf::Vector2i m_mouseDelta; // vector of mouse position change in this frame

    /// SELECTION
    //bool               m_selecting;         // if selection is being made
    //sf::Vector2f       m_selectionStartPos; // start of dragging selection box
    //sf::Vector2f       m_selectionEndPos;   // end of dragging selection box
    //sf::RectangleShape m_selectionRect;     // rectngle for displaying selection

    // Cursorshade
    //sf::RectangleShape m_cursorShade; // rectangle for highlighing tile under cursor
};

#endif //GEARSAPP_HPP
