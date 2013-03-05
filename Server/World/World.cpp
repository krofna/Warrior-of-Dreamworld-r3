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
#include "World.hpp"

#include "ObjectMgr.hpp"
#include "Database.hpp"
#include "ObjectAccessor.hpp"

#include "Creature.hpp"
#include "Player.hpp"
#include "Map.hpp"

#include "CreatureAI.hpp"

#include "Pathfinder.hpp"

#include "Shared/Log.hpp"

#include "CommandHandler.hpp"

#include <boost/bind.hpp>

World::World() :
IsRunning   (true)
{
    sLog.Write(FILTER_LOADING, LEVEL_INFO, "Factories created.");
    ObjectMgr::CreateInstance();
    sLog.Write(FILTER_LOADING, LEVEL_INFO, "ObjectMgr created.");
    ObjectAccessor::CreateInstance();
    sLog.Write(FILTER_LOADING, LEVEL_INFO, "ObjectAccessor created.");
    Pathfinder::CreateInstance();
    sLog.Write(FILTER_LOADING, LEVEL_INFO, "Pathfinder created.");
}

World::~World()
{
}

void World::Load()
{
    try
    {
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Registering static factories...");

        Factory::Register <Creature>     ("Creature");
        Factory::Register <Player>       ("Player");

        Factory::Register <Map>          ("Map");

        Factory::Register <CreatureAI>   ("CreatureAI");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Static factories registered.");
    
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading creature templates...");
        ObjectMgr::GetInstance()->LoadCreatureTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Creature templates loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading creature quests...");
        ObjectMgr::GetInstance()->LoadCreatureQuests();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Creature quests loaded.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading spell templates...");
        ObjectMgr::GetInstance()->LoadSpellTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Spells loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading gameobject templates...");
        ObjectMgr::GetInstance()->LoadGameObjectTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Gameobject templates loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading map templates...");
        ObjectMgr::GetInstance()->LoadMapTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Map templates loaded.");

//        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading scripts...");
//        LoadScripts();
//        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Scripts loaded.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Initializing pathfinder...");
        Pathfinder::Initialize();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Pathfinder initialized.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading maps...");
        QueryResult Result = std::move(WorldDB->Query("SELECT * FROM `map`"));
        while (Result->next())
        {
            Map* p_Map = Factory::Load <Map> ("Map", std::move(Result)); // What do you want to do with p_Map ?
            // sLog.Write(FILTER_LOADING, LEVEL_INFO, "Map %i loaded", p_Map->GetGUID());
            sLog.Write(FILTER_LOADING, LEVEL_INFO, "One map loaded.");
        }
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Maps loaded.");
    }
    catch (sql::SQLException& e)
    {
        sLog.Write(FILTER_LOADING, LEVEL_FATAL, "SQL Exception: %s", e.what());
        exit(1);
    }
    catch (std::exception& e)
    {
        sLog.Write(FILTER_LOADING, LEVEL_FATAL, "Exception: %s", e.what());
        exit(2);
    }
}

void World::CLI()
{
    std::string Input;

    while (IsRunning)
    {
        std::cout << "WoD> " << std::flush;
        std::getline(std::cin, Input);

        if (Input == "exit")
            break;
            
        CommandHandler Handler(Input);

        try
        {
            Handler.ExecuteCommand();
        }
        catch (CommandHandler::BadCommand& /*e*/)
        {
            sLog.Write(LEVEL_WARNING, FILTER_COMMANDS, "Bad command!");
        }
        catch (sql::SQLException& e)
        {
            sLog.Write(LEVEL_ERROR, FILTER_COMMANDS, e.what());
            sLog.Flush();
        }
    }
    IsRunning = false;
}

void World::Update(uint32 diff)
{
    // Update all updateable objects
//    ObjectHolder<Item>::Execute(boost::bind(&Item::Update, _1, diff));
    ObjectHolder<Map>::Execute(boost::bind(&Map::Update, _1, diff));
//    ObjectHolder<GameObject>::Execute(boost::bind(&GameObject::Update, _1, diff));
//    ObjectHolder<Pet>::Execute(boost::bind(&Pet::Update, _1, diff));
    ObjectHolder<Creature>::Execute(boost::bind(&Creature::Update, _1, diff));
//    ObjectHolder<Vehicle>::Execute(boost::bind(&Vehicle::Update, _1, diff));
    ObjectHolder<Player>::Execute(boost::bind(&Player::Update, _1, diff));
    
    // Actually send update to clients
    ObjectHolder<Player>::Execute(boost::bind(&Player::SendUpdate, _1));
}

void World::KickAll()
{
    // WTF.
}

bool World::IsStopped()
{
    return !IsRunning;
}
