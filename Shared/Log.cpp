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

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

Log sLog;

Log::Log() :
File    ("RyanLikesAnimes.log")
{

}

Log::Log(std::string const& FileName) :
File    (FileName.c_str())
{

}

void Log::Load(std::string const& ConfigSection)
{
    const int amount = (6 * 2);
    for (int i = 0; i < amount; i += 2)
    {
        std::vector<std::string> Pair;
        std::string Filter = Filters[i / 2];
        std::string StringLogConfig = ConfigSystem::GetInstance()->GetValue<std::string>(ConfigSection, Filter);
        boost::algorithm::split(Pair, StringLogConfig, boost::algorithm::is_any_of(";"));

        try
        {
            FilterLevels[i % 2][i / 2] = ToType<uint8>(Pair.at(0));
            FilterLevels[(i + 1) % 2][(i + 1) / 2] = ToType<uint8>(Pair.at(1));
        }
        catch (std::out_of_range const& ex)
        {
            std::cerr << "[Log Init] : Malformed config file." << std::endl;
        }
    }
}

void Log::Flush()
{
    std::lock_guard<std::mutex> Lock(LogMutex);
    std::cout << std::flush;
    File << std::flush;
}
