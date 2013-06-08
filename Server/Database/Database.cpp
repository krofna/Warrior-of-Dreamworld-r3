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
#include "Database.hpp"
#include "Shared/Log.hpp"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

Database::Database() : Driver(get_driver_instance())
{
}

Database::~Database()
{
}

void Database::Load(std::string const& ConfigSection)
{
    std::string DatabaseConfigLine = ConfigSystem::GetInstance()->GetValue<std::string>(ConfigSection, ConfigName);

    std::vector<std::string> SubStrings;
    boost::algorithm::split(SubStrings, DatabaseConfigLine, boost::algorithm::is_any_of(";"));

    std::string hostName = SubStrings[0];
    std::string userName = SubStrings[1];
    std::string password = SubStrings[2];
    std::string databaseName = SubStrings[3];

    Connection.reset(Driver->connect(hostName, userName, password));
    Connection->setSchema(databaseName);
    Statement.reset(Connection->createStatement());

    sLog.Write(LEVEL_DEBUG, LOG_CONSOLE, "Connection %s@%s with password : %s - Database %s", hostName, userName, password, databaseName); 
}

void Database::SetConfig(std::string const& Name)
{
    ConfigName = Name;
}

void Database::Execute(const char* Sql)
{
    Statement->execute(Sql);
}

QueryResult Database::Query(const char* Sql)
{
    PStatement.reset(Connection->prepareStatement(Sql));
    return QueryResult(PStatement->executeQuery());
}

uint64 Database::GenerateGUID()
{
    QueryResult result = DatabaseFactory::GetInstance()->Get()->Query("SELECT UUID_SHORT();");
    result->next();
    return result->getUInt64(1);
}

bool DatabaseFactory::CreateDatabase(std::string const& Name, std::string const& ConfigSection)
{
    m_Databases[Name] = std::make_shared<Database>();
    m_Databases[Name]->SetConfig(Name);
    m_Databases[Name]->Load(ConfigSection);
    
    return true; // TODO: Test if the connection have been made.
}

void DatabaseFactory::RemoveDatabase(std::string const& Name)
{
    m_Databases.erase(Name);
}

std::shared_ptr<Database> DatabaseFactory::Get(std::string const& Name) const
{
    auto Iter = m_Databases.find(Name);
    return Iter == m_Databases.end() ? nullptr : (*Iter).second;
}

std::shared_ptr<Database> DatabaseFactory::Get() const
{
    return (*(m_Databases.begin())).second; // TODO: Check if there is element in the map.
}
