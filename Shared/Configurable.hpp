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
#include "Utility.hpp"

class Configurable
{
public:
    virtual void LoadFromConfig(std::ifstream& Config) = 0;
protected:
    template <class T> void GetNextToken(std::ifstream& Config, T& Data);
    template <class T> T GetNextToken(std::ifstream& Config);
};

template <class T> void Configurable::GetNextToken(std::ifstream& Config, T& Data)
{
    if (!Config)
        throw std::runtime_error("Config stream is not open !");
    
    std::string p;
    Config >> p;
    while (p[0] == '#')
        Config >> p;

    Data = ToType<T>(p);
}

template <class T> T Configurable::GetNextToken(std::ifstream& Config)
{
    T Data;
    GetNextToken(Config, Data);
    return Data;
}

#endif
