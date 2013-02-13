/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2013 Mislav Blazevic

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
#ifndef MAIN_HPP
#define MAIN_HPP

#include "Singleton.hpp"

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
using namespace boost::posix_time;

class Main : public Singleton<Main>
{
public:
    Main();
    ~Main();

    void Load(int argc, char** argv);
    void Run();
    int GetRetVal();

private:
    void WorldLoop();

    ptime GetCurrentTime();
    time_duration GetDiff(ptime& Old, ptime& New);

    int RetVal;
    ptime CurrentTime = 0;
    ptime PreviousTime = GetCurrentTime();
    ptime PreviousSleepTime = 0;
    ptime ServerStartTime
    std::vector<boost::shared_ptr<boost::thread> > Threads;
    boost::asio::deadline_timer HeartbeatTimer;
    boost::asio::io_service io;
};

#endif