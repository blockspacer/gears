#include "Settings.hpp"
#include "stdafx.hpp"


using namespace sf;
using namespace ge;


Settings::Settings()
    : c_confFile("cfg/Conf.ini")
    , c_keysFile("cfg/Keys.ini")
    , m_confParser(c_confFile)
    , m_keysParser(c_keysFile)
    , m_gui(std::make_shared<tgui::ChildWindow>())
{

    // init defaults
    init();

    // try to load from file
    // if it fails, fill parser with defaults
    load();

    // save the parser with the initial settings
    save();

    // finally init the gui
    initGui();
}


Settings::~Settings()
{
}

void Settings::init()
{
    // Init default fallback values and limits

    conf.resolution        = make_config<VideoMode>("Screen Resolution", VideoMode::getDesktopMode(), VideoMode::getFullscreenModes());
    conf.fullScreen        = make_config<bool>("Fullscreen Mode", false);
    conf.vSync             = make_config<bool>("Vertical Sync", true);
    conf.hwCursor          = make_config<bool>("Hardware Cursor", true);
    conf.mouseSpeed        = make_config<float>("Mouse Speed", 1.f, 0.25f, 4.f, 0.05f);
    conf.panSpeed          = make_config<int>("Keyboard Scroll Speed", 1000, 100, 3000, 100);
    conf.invertMouseScroll = make_config<bool>("Invert Mouse Scroll", false);


    // Init default keys

    keys[HK_UP]    = HotkeyConfig("Scroll Up", sf::Keyboard::Up, sf::Keyboard::W);
    keys[HK_DOWN]  = HotkeyConfig("Scroll Down", sf::Keyboard::Down, sf::Keyboard::S);
    keys[HK_LEFT]  = HotkeyConfig("Scroll Left", sf::Keyboard::Left, sf::Keyboard::A);
    keys[HK_RIGHT] = HotkeyConfig("Scroll Right", sf::Keyboard::Right, sf::Keyboard::D);

    keys[HK_ZOOM_IN]  = HotkeyConfig("Zoom In", sf::Keyboard::PageUp);
    keys[HK_ZOOM_OUT] = HotkeyConfig("Zoom Out", sf::Keyboard::PageDown);

    keys[HK_DIG]   = HotkeyConfig("Dig Tool", sf::Keyboard::G);
    keys[HK_BUILD] = HotkeyConfig("Build Tool", sf::Keyboard::B);
}


void Settings::load()
{
    /// LOAD FROM FILE

    if(!m_confParser.loadFromFile()) {
        std::cerr << "Cold not load configuration file, using defaults" << std::endl;
    }
    if(!m_keysParser.loadFromFile()) {
        std::cerr << "Cold not load key bindings file, using defaults" << std::endl;
    }

    /// READ CONFIGS

    readConf(conf.resolution);
    readConf(conf.fullScreen);
    readConf(conf.vSync);
    readConf(conf.hwCursor);

    readConf(conf.mouseSpeed);
    readConf(conf.panSpeed);
    readConf(conf.invertMouseScroll);

    /// READ KEYS

    for(int i = 0; i < ge::HK_COUNT; ++i) {
        readKey(static_cast<ge::HotkeyId>(i));
    }

    m_confParser.print();
    m_keysParser.print();
}

void Settings::save()
{
    /// WRITE CONFIGS

    writeConf(conf.resolution);
    writeConf(conf.fullScreen);
    writeConf(conf.vSync);
    writeConf(conf.hwCursor);

    writeConf(conf.mouseSpeed);
    writeConf(conf.panSpeed);
    writeConf(conf.invertMouseScroll);

    /// WRITE KEYS

    for(int i = 0; i < ge::HK_COUNT; ++i) {
        writeKey(static_cast<ge::HotkeyId>(i));
    }

    m_confParser.print();
    m_keysParser.print();


    /// SAVE TO FILE

    if(!m_confParser.saveToFile()) {
        std::cerr << "Cold not save configuration file" << std::endl;
    }
    if(!m_keysParser.saveToFile()) {
        std::cerr << "Cold not save keybindings file" << std::endl;
    }
}


void Settings::initGui()
{
}

void Settings::open()
{
}

void Settings::close()
{
}



void Settings::readKey(ge::HotkeyId keyId)
{
    HotkeyPair keyPair = keys[keyId].getBoth();
    m_keysParser.get(keys[keyId].getShortName(), keyPair);
    keys[keyId].setBoth(keyPair);
}

void Settings::writeKey(ge::HotkeyId keyId)
{
    m_keysParser.set(keys[keyId].getShortName(), keys[keyId].getBoth());
}
