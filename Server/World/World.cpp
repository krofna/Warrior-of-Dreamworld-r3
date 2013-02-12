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
#include "Shared/ObjectMgr.hpp"
#include "Database.hpp"
#include "scripts/ScriptLoader.hpp"
#include "Log.hpp"
#include "CommandHandler.hpp"
#include "Map.hpp"

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
    ObjectMgr::DestroyInstance();
    ObjectAccessor::DestroyInstance();
    Pathfinder::DestroyInstance();
}

void World::Load()
{
    try
    {
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Registering static factories...");

        Factory::Register <Creature>   ("Creature");
        Factory::Register <Player>     ("Player");
        Factory::Register <Item>       ("Item");
        Factory::Register <GameObject> ("GameObject");
        Factory::Register <Pet>        ("Pet");
        Factory::Register <Vehicle>    ("Vehicle");

        Factory::Register <Map>        ("Map");
        Factory::Register <Bag>        ("Bag");

        Factory::Register <CreatureAI>   ("CreatureAI");
        Factory::Register <GameObjectAI> ("GameObjectAI");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Static factories registered.");
    
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading creature templates...");
        sObjectMgr.LoadCreatureTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Creature templates loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading creature quests...");
        sObjectMgr.LoadCreatureQuests();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Creature quests loaded.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading spell templates...");
        sObjectMgr.LoadSpellTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Spells loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading gameobject templates...");
        sObjectMgr.LoadGameObjectTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Gameobject templates loaded.");
        
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading map templates...");
        sObjectMgr.LoadMapTemplates();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Map templates loaded.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading scripts...");
        LoadScripts();
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Scripts loaded.");

        sLog.Write("Initializing pathfinder...");
        Pathfinder::Initialize();
        sLog.Write("Pathfinder initialized.");

        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Loading maps...");
        QueryResult Result(WorldDatabase.Query("SELECT * FROM `map`"));
        while (Result->next())
            Factory::Load <Map> ("Map", Result);
        sLog.Write(FILTER_LOADING, LEVEL_INFO, "Maps loaded.");
    }
    catch (sql::SQLException& e)
    {
        sLog.Write(FILTER_LOADING, LEVEL_FATAL, "SQL Exception: ", e.what());
        exit(1);
    }
    catch (std::exception& e)
    {
        sLog.Write(FILTER_LOADING, LEVEL_FATAL, "Exception: ", e.what());
        exit(2);
    }
}

void World::ConsoleInput()
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
    // TODO: Should any specific order be maintained?
    ObjectHolder<Item>::Execute(boost::bind(&Item::Update, _1, diff));
    ObjectHolder<Creature>::Execute(boost::bind(&Creature::Update, _1, diff));
    ObjectHolder<Player>::Execute(boost::bind(&Player::Update, _1, diff));
    ObjectHolder<GameObject>::Execute(boost::bind(&GameObject::Update, _1, diff));
    ObjectHolder<Pet>::Execute(boost::bind(&Pet::Update, _1, diff));
    ObjectHolder<Vehicle>::Execute(boost::bind(&Vehicle::Update, _1, diff));
    ObjectHolder<Map>::Execute(boost::bind(&Map::Update, _1, diff));
    
    // Actually send update to clients
    ObjectHolder<Player>::Execute(boost::bind(&Player::SendUpdate, _1));
}

bool World::IsStopped()
{
    return !IsRunning;
}
