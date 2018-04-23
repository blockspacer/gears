#pragma once
#ifndef MKHOTKEY_H
#define MKHOTKEY_H

#include "ConfigBase.hpp"
#include "Hotkey.hpp"

namespace ge {

class HotkeyConfig : public ge::ConfigBase<HotkeyPair>
{
public:
    HotkeyConfig()
        : HotkeyConfig(""){};

    HotkeyConfig(std::string name,
                 Hotkey      defaultPrimary   = Hotkey(),
                 Hotkey      defaultSecondary = Hotkey())
        : HotkeyConfig(name, std::make_pair(defaultPrimary, defaultSecondary)){};

    HotkeyConfig(std::string name, HotkeyPair defaults)
        : ge::ConfigBase<HotkeyPair>(name, defaults){};

    void setPrimary(Hotkey hotkey)
    {
        HotkeyPair value = m_property.get();
        value.first      = hotkey;
        m_property.set(value);
    }
    Hotkey getPrimary()
    {
        return m_property.get().first;
    }

    void setSecondary(Hotkey hotkey)
    {
        HotkeyPair value = m_property.get();
        value.second     = hotkey;
        m_property.set(value);
    }
    Hotkey getSecondary()
    {
        return m_property.get().second;
    }

    void setBoth(HotkeyPair hotkeys)
    {
        m_property.set(hotkeys);
    }
    HotkeyPair getBoth()
    {
        return m_property.get();
    }

    void setDefaultPrimary(Hotkey hotkey)
    {
        m_default.first = hotkey;
    }
    Hotkey getDefaultPrimary()
    {
        return m_default.first;
    }

    void setDefaultSecondary(Hotkey hotkey)
    {
        m_default.second = hotkey;
    }
    Hotkey getDefaultSecondary()
    {
        return m_default.first;
    }

    void setDefaultBoth(HotkeyPair hotkeys)
    {
        m_default = hotkeys;
    }
    HotkeyPair getDefaultBoth()
    {
        return m_default;
    }
};
}

#endif // !MKHOTKEY_H
