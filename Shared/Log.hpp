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
#ifndef LOG_HPP
#define LOG_HPP

#include "Configurable.hpp"
#include "Utility.hpp"
#include "LogFilter.hpp"
#include "Shared/BasicTypes.hpp"

#include <iostream>
#include <mutex>

enum LogLevel
{
    LEVEL_INFO      = 0,
    LEVEL_DEBUG     = 1,
    LEVEL_WARNING   = 2,
    LEVEL_ERROR     = 3,
    LEVEL_FATAL     = 4
};

enum LogType
{
    LOG_FILE        = 0,
    LOG_CONSOLE     = 1,
    LOG_MAX         = 2
};

class Log : public Configurable
{
public:
    Log(std::string FileName);
    void LoadFromConfig(std::ifstream& Config);
    
    template<typename... Values> void Write(uint8 Level, uint8 Filter, std::string const& String, Values... Vals);
    void Flush();
private:
    std::ofstream File;
    uint8 FilterLevels[LOG_MAX][FILTER_MAX];
    std::mutex LogMutex;
};

template<typename... Values> void Log::Write(uint8 Level, uint8 Filter, std::string const& String, Values... Vals)
{
    bool DoWrite[LOG_MAX] = { false, false };
    DoWrite[LOG_CONSOLE] = Level < FilterLevels[LOG_CONSOLE][Filter];
    DoWrite[LOG_FILE] = Level < FilterLevels[LOG_FILE][Filter];

    if (*(uint16*)&DoWrite[0] == 0)
        return;
    
    std::string Formated = Format(String, Vals...);

    LogMutex.lock();
    if (DoWrite[LOG_CONSOLE])
        std::cout << Formated;
    if (DoWrite[LOG_FILE])
        File << Formated;
    LogMutex.unlock();
}

extern Log sLog;

#endif
