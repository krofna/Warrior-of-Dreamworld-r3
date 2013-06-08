/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic, Ryan Lahfa

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef CONFIGURABLE_HPP
#define CONFIGURABLE_HPP

#include <fstream>
#include <limits>
#include <stdexcept>
#include <map>
#include <boost/variant.hpp>
#include <boost/variant/get.hpp>
#include "Utility.hpp"
#include "Singleton.hpp"

class Configurable
{
public:
    virtual void Load(std::string const& ConfigSection) = 0;
};

class ConfigSystem : public Singleton<ConfigSystem>
{
    friend class Singleton<ConfigSystem>;
    typedef boost::variant<char, int, double, float, std::string> ConfigValue; // TODO : Extend to custom types if needed.
    ConfigSystem();
    public:

        void Load(std::string const& FileName);

        std::vector<std::string> GetSections() const;
        std::vector<std::string> GetKeysFromSection(std::string const& Section) const;

        template <class T> 
        T GetValue(std::string const& Section, std::string const& Key) const;

        bool SectionExist(std::string const& Section) const;
        bool KeyExist(std::string const& Section, std::string const& Key) const;

    private:
        void ReadFile(std::string const& FileName);
        void AddSection(std::string const& Section);
        void AddConfigPair(std::string const& Section, std::string const& Key, std::string const& Value);
    
    private:
        std::vector<std::string> Sections;
        std::map<std::string, std::map<std::string, ConfigValue> > Values;
};

template <class T>
T ConfigSystem::GetValue(std::string const& Section, std::string const& Key) const
{
    if (SectionExist(Section) && KeyExist(Section, Key))
    {
        auto it = Values.find(Section);
        ConfigValue v = it->second.find(Key)->second;        
        return boost::get<T>(v);
    }
    else
        throw std::runtime_error("Unknown or invalid section or key.");
}


#endif
