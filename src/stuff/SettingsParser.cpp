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
#include "stdafx.hpp"
#include "SettingsParser.hpp"


#include <fstream>
#include <iostream>
#include <locale>
#include <sstream>
#include <vector>


SettingsParser::SettingsParser(std::string filename)
    : m_isChanged(false)
    , m_filename(filename)
{
}


SettingsParser::~SettingsParser()
{
}


bool SettingsParser::loadFromFile()
{
    m_fileContents.clear();

    // open file for reading
    std::ifstream ifs(m_filename);
    if(!ifs.is_open()) {
        std::cerr << "Error: Unable to open settings file \"" << m_filename
                  << "\" for reading!" << std::endl;
        return false;
    }

    // get fil line by line
    std::string line;
    while(std::getline(ifs, line)) {
        // parse line and add itt to th vector of contents
        StringPair keyValuePair = parseLine(line);
        m_fileContents.push_back(keyValuePair);

        // if the line is an actual setting save it to the data map
        if(!keyValuePair.first.empty() && keyValuePair.first != "#") {
            m_data[keyValuePair.first] = keyValuePair.second;
        }
    }

    // close file & reset changed state
    ifs.close();
    m_isChanged = false;
    return true;
}

bool SettingsParser::saveToFile()
{
    // if settings didn't change at all, don't even bother
    if(!m_isChanged) {
        return true;
    }
    m_isChanged = false;

    // open the file for writing
    std::ofstream ofs(m_filename);
    if(!ofs.is_open()) {
        std::cerr << "Error: Unable to open settings file \"" << m_filename
                  << "\" for writing!" << std::endl;
        return false;
    }

    ////create tmp map for keeping track of items
    // std::map<std::string, std::string> tmpMap = m_data;
    //// for each line in the contents vector write to file
    // for( auto linePair : m_fileContents )
    //{
    //	// empty line
    //	if( linePair.first.length() == 0 )
    //	{
    //		ofs << std::endl;
    //	}
    //	// comment line
    //	else if( linePair.first.at( 0 ) == '#' )
    //	{
    //		ofs << "#" << linePair.second << std::endl;
    //	}
    //	// data line
    //	else
    //	{
    //		linePair.second = tmpMap.at( linePair.first );
    //		tmpMap.erase( linePair.first );
    //		ofs << linePair.first << " = " << linePair.second << std::endl;
    //	}
    //}

    // bah, just write the values
    // TODO: improve this method
    for(auto dataPair : m_data) {
        ofs << dataPair.first << " = " << dataPair.second << std::endl;
    }


    // that's it
    ofs.close();
    return true;
}


std::pair<std::string, std::string>
SettingsParser::parseLine(const std::string& line) const
{
    // empty line
    if(line.size() == 0) {
        return std::make_pair(std::string(), std::string());
    }
    // comment line
    if(line.at(0) == '#') {
        return std::make_pair(std::string("#"), line.substr(1));
    }
    // data line
    StringPair        dataPair;
    std::stringstream ss(line);

    // get key part of line
    std::getline(ss, dataPair.first, '=');
    ge::stripSpaces(dataPair.first);

    // skip spaces after '='
    while(ss.peek() == ' ') {
        ss.ignore();
    }

    // get data part of the line
    std::getline(ss, dataPair.second);

    return dataPair;
}


void SettingsParser::print() const
{
    for(auto& element : m_data) {
        std::cout << element.first << " = " << element.second << std::endl;
    }
    std::cout << std::endl;
}

bool SettingsParser::isChanged() const
{
    return m_isChanged;
}
