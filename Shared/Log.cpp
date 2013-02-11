/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic

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
#include "Log.hpp"

Log sLog;

Log::Log(std::string FileName) :
File    (FileName)
{
}

void Log::LoadFromConfig(std::ifstream& Config)
{
    for (int i = 0; i < 6 * 2; ++i)
        GetNextToken(Config, FilterLevels[i % 2][i / 2]);
}

void Log::Flush()
{
    boost::mutex::scoped_lock Lock(LogMutex);
    std::cout << std::flush;
    File << std::flush;
}
