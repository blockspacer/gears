////////////////////////////////////////////////////////////
// Copyright (c) 2016 Maximilian Wagenbach
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgement in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
////////////////////////////////////////////////////////////

#ifndef SETTINGSPARSER_INCLUDE
#define SETTINGSPARSER_INCLUDE

#include "misc/textconvert.hpp"

#include <map>


class SettingsParser
{
    typedef std::pair<std::string, std::string> StringPair;

public:
    explicit SettingsParser(std::string filename);
    ~SettingsParser();

    // load settings from file
    bool loadFromFile();
    // save settings to file; default = the opened file
    bool saveToFile();

    bool isChanged() const;

    // Get key into the given value reference
    // returns true if key was found and the value has bee read
    // returns false if value unchanged
    template <typename T>
    bool get(const std::string& key, T& value) const;

    // Set key to the given value
    // if successful and the new value is different it returns true
    // if data left unchanged it returns false
    template <typename T>
    bool set(const std::string& key, const T& value);

    void print() const;

private:
    StringPair parseLine(const std::string& line) const;

    bool        m_isChanged;
    std::string m_filename;
    std::map<std::string, std::string> m_data;
    std::vector<StringPair> m_fileContents;
};

/// GET SETTING

template <typename T>
inline bool SettingsParser::get(const std::string& key, T& value) const
{
    /*
  auto it = m_data.find( key );
  if( it != m_data.end() )
  {
          value = mk::strToType<T>( it->second );
          return true;
  }
  */
    // TODO: Fix linker error
    return false;
}

/// SET SETTING

template <typename T>
inline bool SettingsParser::set(const std::string& key, const T& value)
{
    /*
  // the [] operator replaces the value if the key is found, if not it creates a
  new element
  if( key.length() != 0 )
  {
          std::string newData = mk::typeToStr<T>( value );
          if( m_data[key] != newData )
          {
                  m_data[key] = newData;
                  m_isChanged = true;
                  return true;
          }
  }
  */
    // TODO: Fix linker error
    return false;
}



#endif // SETTINGSPARSER_INCLUDE
