#ifndef CONFIGBASE_HPP
#define CONFIGBASE_HPP

#include "include/Property.hpp"
#include "misc/textconvert.hpp"

#include <string>

namespace ge {

template <typename T>
class ConfigBase
{
public:
    // constructor
    ConfigBase(const std::string& name, T defaultValue);
    // destructor
    ~ConfigBase();

    // set the name of the configuration setting
    void setName(std::string name);
    // get the name of the configuration setting
    const std::string& getName() const;
    // get a shorter name of the configuration setting with no spaces
    const std::string& getShortName() const;

    // set the value of this configuration setting
    virtual void setValue(T value);
    // get the value of this configuration setting
    T getValue() const;

    // set the default value
    void setDefault(T defaultValue);
    // get the default value
    T getDefault() const;

    // reset value to defaults
    void resetValue();

    // get the property of the configuration for obsevation purposes
    const Property<T>& getProperty();

protected:
    std::string m_name;
    std::string m_shortName;

    T           m_default;
    Property<T> m_property;
};


template <typename T>
inline ConfigBase<T>::ConfigBase(const std::string& name, T defaultValue)
    : m_default(defaultValue), m_property(defaultValue)
{
    setName(name);
}

template <typename T>
inline ConfigBase<T>::~ConfigBase()
{
}

template <typename T>
inline void ConfigBase<T>::setName(std::string name)
{
    m_name      = name;
    m_shortName = ge::strippedSpaces(name);
}

template <typename T>
inline const std::string& ConfigBase<T>::getName() const
{
    return m_name;
}

template <typename T>
inline const std::string& ConfigBase<T>::getShortName() const
{
    return m_shortName;
}

template <typename T>
inline void ConfigBase<T>::setValue(T value)
{
    m_property.set(value);
}

template <typename T>
inline T ConfigBase<T>::getValue() const
{
    return m_property.get();
}

template <typename T>
inline void ConfigBase<T>::setDefault(T defaultValue)
{
    m_default = defaultValue;
}

template <typename T>
inline T ConfigBase<T>::getDefault() const
{
    return m_default;
}

template <typename T>
inline void ConfigBase<T>::resetValue()
{
    m_property.set(m_default);
}

template <typename T>
inline const Property<T>& ConfigBase<T>::getProperty()
{
    return m_property;
}


} //end ns:ge


#endif // !CONFIGBASE_HPP
