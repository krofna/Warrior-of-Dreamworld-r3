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
#include "Main.hpp"
#include "World.hpp"

#define WORLD_HEARTBEAT 50

Main::Main    () :
HeartbeatTimer(io)
{
    ServerStartTime = boost::posix_time::second_clock::local_time();

    World::CreateInstance();
    WorldAcceptor::CreateInstance(io);
}

Main::~Main()
{
    World::DestroyInstance();
    WorldAcceptor::DestroyInstance();
}

ptime Main::GetCurrentTime()
{
    return boost::posix_time::second_clock::local_time() - ServerStartTime;
}

time_duration Main::GetDiff(ptime& Old, ptime& New)
{
    return New - Old;
}

void Main::Load(int argc, char** argv)
{
    WorldDatabase = new Database;
    WorldDatabase->LoadFromConfig();
    CharactersDatabase = new Database;
    CharacterDatabase->LoadFromConfig();
    sLog = new Log;
    sLog.LoadFromConfig();
    sWorld = new World;
    sWorld->Load();
    
    io.post(boost::bind(&World::CLI,            World::GetInstance()));
    io.post(boost::bind(&Main::Run,             Main::GetInstance()));
    io.post(boost::bind(&WorldAcceptor::Start,  WorldAcceptor::GetInstance()));
}

void Main::WorldLoop()
{
    while (!sWorld.IsStopped())
    {
        CurrentTime = GetCurrentTime();
        time_duration diff = GetDiff(PreviousTime, CurrentTime);
        sWorld->Update(diff.total_milliseconds());
        PreviousTime = CurrentTime;

        if (diff <= WORLD_HEARTBEAT + PreviousSleepTime)
        {
            PreviousSleepTime = WORLD_HEARTBEAT + PreviousSleepTime - diff;
            HeartbeatTimer.expires_at(PreviousSleepTime);
            HeartbeatTimer.async_wait(boost::bind(&Main::WorldLoop, this));
            return;
        }
        else
            PreviousSleepTime = 0;
    }
    sWorld->KickAll();
}

void Main::Run()
{
    Threads.resize(4, new boost::thread(boost::bind(&boost::asio::io_service::run, &io)))

    CurrentTime = 0;
    PreviousTime = GetCurrentTime();
    PreviousSleepTime = 0;

    io.run();

    for (size_t i = 0; i < Threads.size(); ++i)
        Threads[i]->join();
}

int GetRetVal()
{
    return RetVal;
}

int main(int argc, char** argv)
{
    Main::CreateInstance();
    Main::GetInstance()->Load(argc, argv);
    Main::GetInstance()->Run();
    Main::DestroyInstance();
    return Main::GetInstance()->GetRetVal();
}
