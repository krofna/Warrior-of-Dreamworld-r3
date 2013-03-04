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

#include "Shared/Singleton.hpp"

#include <boost/asio/deadline_timer.hpp>
#include <boost/chrono.hpp>
#include <thread>
#include <memory>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

typedef boost::chrono::milliseconds ms;

class Main : public Singleton<Main>
{
    friend class Singleton;
    Main(boost::asio::io_service& io);
public:
    ~Main();

    void Load(int argc, char** argv);
    void Run();
    int GetRetVal() const;

private:
    void WorldLoop();
    void ProcessOption(std::pair<std::string, std::string> const& opt);

    int RetVal;
    int nThreads;

    std::vector<std::shared_ptr<std::thread> > Threads;
    boost::asio::deadline_timer HeartbeatTimer;
    boost::chrono::high_resolution_clock::time_point OldTime;
    boost::asio::io_service& io;
};

#endif
