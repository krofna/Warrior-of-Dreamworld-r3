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

Database::Database() : Driver(get_driver_instance())
{
}

Database::~Database()
{
}

void Database::LoadFromConfig(std::ifstream& Config)
{
    std::string hostName = GetNextToken<std::string>(Config);
    std::string userName = GetNextToken<std::string>(Config);
    std::string password = GetNextToken<std::string>(Config);
    Connection.reset(Driver->connect(hostName, userName, password));
    Connection->setSchema(GetNextToken<std::string>(Config));
    Statement.reset(Connection->createStatement());
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

bool DatabaseFactory::CreateDatabase(std::string const& Name, std::ifstream& Config)
{
    m_Databases[Name] = std::make_shared<Database>();
    m_Databases[Name]->LoadFromConfig(Config);
    
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
