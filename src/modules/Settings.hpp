#ifndef MKSETTINGS_H
#define MKSETTINGS_H

#include "include/SettingsParser.hpp"
#include "subclasses/Config.hpp"
#include "subclasses/Hotkey.hpp"
#include "subclasses/HotkeyConfig.hpp"

#include <TGUI/TGUI.hpp>
#include <Thor/Input.hpp>

namespace ge {

template <typename T>
using config_ptr = std::unique_ptr<ge::Config<T>>;

template <typename T, typename... Args>
config_ptr<T> make_config(Args&&... args)
{
    return std::make_unique<ge::Config<T>>(std::forward<Args>(args)...);
}

class Settings
{
public:
    struct Configuration
    {
        ge::config_ptr<sf::VideoMode> resolution;
        ge::config_ptr<bool>          fullScreen;
        ge::config_ptr<bool>          vSync;
        ge::config_ptr<bool>          hwCursor;

        ge::config_ptr<float> mouseSpeed; // factor of mouse speed compared to desktop
        ge::config_ptr<int>   panSpeed;   // screen scrol speed in pixels per second
        ge::config_ptr<bool>  invertMouseScroll;
    };

public:
    Settings();
    ~Settings();

    // Initialize settings with default values
    void init();
    // Load the settings from the config files
    void load();
    // Save the settings to the config files
    void save();

    // create the settings panel gui
    void initGui();
    // open up the settings panel
    void open();
    // close the settings panel
    void close();


    Configuration conf; // the configuration structure

    std::map<ge::HotkeyId, ge::HotkeyConfig> keys;

protected:
    template <typename T>
    void readConf(const ge::config_ptr<T>& confPtr);
    template <typename T>
    void writeConf(const ge::config_ptr<T>& confPtr);

    void readKey(ge::HotkeyId keyId);
    void writeKey(ge::HotkeyId keyId);

private:
    const std::string c_confFile;
    const std::string c_keysFile;

    SettingsParser m_confParser; // parser for the Config.ini
    SettingsParser m_keysParser; // parser for the Keys.ini

    std::shared_ptr<tgui::ChildWindow> m_gui; // the settings window
};

template <typename T>
inline void Settings::readConf(const ge::config_ptr<T>& confPtr)
{
    ge::Config<T>* p     = confPtr.get();
    T              value = p->getValue();
    m_confParser.get(p->getShortName(), value);
    p->setValue(value);
}

template <typename T>
inline void Settings::writeConf(const ge::config_ptr<T>& confPtr)
{
    ge::Config<T>* p = confPtr.get();
    m_confParser.set(p->getShortName(), p->getValue());
}


} // end ns:ge

#endif // !MKSETTINGS_H
