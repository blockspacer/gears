#ifndef CONFIG_HPP
#define CONFIG_HPP

#include "ConfigBase.hpp"

#include <vector>

namespace ge {

// The structure of each configuration setting
template<typename T>
class Config : public ConfigBase<T>
{
public:
	// constructor with no restrictions
	Config( const std::string& name, T defaultValue );
	// constructor with limited values, if step is 0 it is not considered
	Config( const std::string& name, T defaultValue, T minValue, T maxValue, T step = 0 );
	// constructor with list of allowed values
	Config( const std::string& name, T defaultValue, std::vector<T> allowedValues );
	// destructor
	~Config();

	// set the value of the configuration setting,
	// value will be clamped to the limits
	// or set to default if doesn't match allowed list
	virtual void setValue( T value );

	// set the limits the value can have; value will be updated
	void setLimits( T minValue, T maxValue, T step = 0 );
	// get the minimum limit of the value
	T getMin() const;
	// get the maximum limit of the value
	T getMax() const;
	// get the step amount of the value
	T getStep() const;
	// is the value bound by limits?
	bool isLimited() const;

	// set the allowed list of values; value will be updated
	void setAllowedValues( std::vector<T> allowedValues );
	// get the allowed values
	std::vector<T> getAllowedValues() const;
	// is the value constrained to the selected values only?
	bool isAllowedOnly() const;

	// unsets all restrictions
	void setNoRestrictions();
	// is the value restricted by any means?
	bool isRestricted() const;

protected:

	using ConfigBase<T>::m_default;
	using ConfigBase<T>::m_property;

	bool m_limited;
	T m_minValue;
	T m_maxValue;
	T m_step;

	bool m_allowedOnly;
	std::vector<T> m_allowedValues;

};

/// TEMPLATED DEFINITIONS

template<typename T>
inline Config<T>::Config( const std::string& name, T defaultValue )
	: ConfigBase<T>( name, defaultValue )
{
	setNoRestrictions();
}

template<typename T>
inline Config<T>::Config( const std::string& name, T defaultValue, T minValue, T maxValue, T step ) :
	Config( name, defaultValue )
{
	setLimits( minValue, maxValue, step );
}

template<typename T>
inline Config<T>::Config( const std::string& name, T defaultValue, std::vector<T> allowedValues ) :
	Config( name, defaultValue )
{
	setAllowedValues( allowedValues );
}

template<typename T>
inline Config<T>::~Config()
{}


template<typename T>
inline void Config<T>::setValue( T value )
{
	if( m_limited )
	{
		m_property.set( clamp( value, m_minValue, m_maxValue ) );
		return;
	}
	if( m_allowedOnly )
	{
		for( auto i : m_allowedValues )
		{
			if( i == value )
			{
				m_property.set( value );
				return;
			}
		}
		m_property.set( m_default );
			return;
	}
	m_property.set( value );
}

template<typename T>
void Config<T>::setLimits( T minValue, T maxValue, T step )
{
	m_allowedOnly = false;
	m_limited = true;
	m_minValue = minValue;
	m_maxValue = maxValue;
	m_step = step;
	setValue( this->getValue() );
}

template<typename T>
T Config<T>::getMin() const
{
	return m_minValue;
}

template<typename T>
T Config<T>::getMax() const
{
	return m_maxValue;
}

template<typename T>
T Config<T>::getStep() const
{
	return m_step;
}

template<typename T>
bool Config<T>::isLimited() const
{
	return m_limited;
}

template<typename T>
void Config<T>::setAllowedValues( std::vector<T> allowedValues )
{
	m_limited = false;
	m_allowedOnly = true;
	m_allowedValues = allowedValues;
	setValue( this->getValue() );
}

template<typename T>
std::vector<T> Config<T>::getAllowedValues() const
{
	return m_allowedValues;
}

template<typename T>
bool Config<T>::isAllowedOnly() const
{
	return m_allowedOnly;
}

template<typename T>
void Config<T>::setNoRestrictions()
{
	m_limited = false;
	m_allowedOnly = false;
}

template<typename T>
bool Config<T>::isRestricted() const
{
	return m_limited || m_allowedOnly;
}

}

#endif // !CONFIG_HPP
