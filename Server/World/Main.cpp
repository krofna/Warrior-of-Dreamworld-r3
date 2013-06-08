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
#include "WorldAcceptor.hpp"
#include "Shared/Log.hpp"

#define WORLD_HEARTBEAT 50

Main::Main (boost::asio::io_service& r_io) :
io(r_io),
HeartbeatTimer(r_io),
nThreads(1)
{
    World::CreateInstance();
    WorldAcceptor::CreateInstance(r_io);
    DatabaseFactory::CreateInstance();
}

Main::~Main()
{
}

void Main::Load(int argc, char** argv)
{
    std::vector<std::string> Arguments(argc - 1);
    std::copy(argv + 1, argv + argc, Arguments.begin());

    if (Arguments.size() > 0)
    {
        for (size_t i = 0 ; i < Arguments.size() ; ++i)
        {
            std::pair<std::string, std::string> opt = SplitPair(Arguments[i], '=');
            ProcessOption(opt);          
        }
    }

    
    // Config system init
    ConfigSystem::CreateInstance();
    ConfigSystem::GetInstance()->Load("LogConfig.conf");
    ConfigSystem::GetInstance()->Load("WorldServer.conf");

    // Log init
    sLog.Load("Logging");
   
    // Database init
    DatabaseFactory::CreateInstance();
    DatabaseFactory::GetInstance()->CreateDatabase("World", "Databases");
    DatabaseFactory::GetInstance()->CreateDatabase("Characters", "Databases");

    // World init
    World::GetInstance()->Load();

    io.post(boost::bind(&World::CLI,            World::GetInstance()));
    io.post(boost::bind(&WorldAcceptor::Accept,  WorldAcceptor::GetInstance()));

    for (size_t i = 0 ; i < nThreads ; ++i)
    {
        auto th = std::make_shared<std::thread>(boost::bind(&boost::asio::io_service::run, boost::ref(io)));
        Threads.push_back(th);
    }
}

void Main::WorldLoop()
{
    if (World::GetInstance()->IsStopped())
    {
        sLog.Write(LOG_CONSOLE, LEVEL_INFO, "World is being stopped... Kicking all...");
        World::GetInstance()->KickAll();
        io.stop();
        return;
    }

    ms DeltaTime = boost::chrono::duration_cast<ms>(boost::chrono::high_resolution_clock::now() - OldTime);
    World::GetInstance()->Update(DeltaTime.count());

    // sLog.Write(LOG_CONSOLE, LEVEL_DEBUG, "Main::WorldLoop() for %i ms", DeltaTime.count());
    OldTime += DeltaTime;

    HeartbeatTimer.expires_at(HeartbeatTimer.expires_at() + boost::posix_time::milliseconds(WORLD_HEARTBEAT));
    HeartbeatTimer.async_wait(boost::bind(&Main::WorldLoop, this));
}

void Main::ProcessOption(std::pair<std::string, std::string> const& opt)
{
    if (opt.first == "--nthread" || opt.first == "-thread")
        nThreads = ToType<int>(opt.second);
    else
       std::cerr << "[LOW-LEVEL - Main::ProcessOptions]: Unknown argument : " << opt.first << std::endl;
}

void Main::Run()
{
    OldTime = boost::chrono::high_resolution_clock::now();
    HeartbeatTimer.expires_from_now(boost::posix_time::milliseconds(WORLD_HEARTBEAT));
    HeartbeatTimer.async_wait(boost::bind(&Main::WorldLoop, this));
    
    io.run();

    std::for_each(Threads.begin(), Threads.end(), [](std::shared_ptr<std::thread>& th) { th->join(); });
}

int Main::GetRetVal() const
{
    return RetVal;
}

int main(int argc, char** argv)
{
    boost::asio::io_service Service;
    Main::CreateInstance(Service);
    Main::GetInstance()->Load(argc, argv);
    Main::GetInstance()->Run();
    return Main::GetInstance()->GetRetVal();
}
