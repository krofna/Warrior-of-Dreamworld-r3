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
#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "Shared/BasicTypes.hpp"
#include "Shared/Configurable.hpp"
#include "Shared/Utility.hpp"
#include "Shared/Singleton.hpp"

#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <memory>
#include <unordered_map>

typedef std::unique_ptr<sql::ResultSet> QueryResult;
typedef std::unique_ptr<sql::Connection> ConnectionPtr;
typedef std::unique_ptr<sql::Statement> StatementPtr;
typedef std::unique_ptr<sql::PreparedStatement> PStatementPtr;

class Database : public Configurable
{
public:
    Database();
    ~Database();

    void LoadFromConfig(std::ifstream& Config);

    void Execute(const char* Sql);
    QueryResult Query(const char* Sql);
    template<typename... Values> void PExecute(std::string const& ToFormat, Values... Vals);
    template<typename... Values> QueryResult PQuery(std::string const& ToFormat, Values... Vals);
    static uint64 GenerateGUID();

private:
    sql::Driver* Driver; // has protected destructor
    ConnectionPtr Connection;
    StatementPtr Statement;
    PStatementPtr PStatement;
};

template<typename... Values> void Database::PExecute(std::string const& Sql, Values... Vals)
{
    Execute(Format(Sql, Vals...).c_str());
}

template<typename... Values> QueryResult Database::PQuery(std::string const& Sql, Values... Vals)
{
    return Query(Format(Sql, Vals...).c_str());
}

class DatabaseFactory : public Singleton<DatabaseFactory>
{
    friend class Singleton<DatabaseFactory>;
    DatabaseFactory() = default;
    public:
    bool CreateDatabase(std::string const& Name, std::ifstream& Config);
    void RemoveDatabase(std::string const& Name);

    std::shared_ptr<Database> Get(std::string const& Name) const;
    std::shared_ptr<Database> Get() const;

    private:
    std::unordered_map<std::string, std::shared_ptr<Database> > m_Databases;
};

#define CharactersDB DatabaseFactory::GetInstance()->Get("Characters")
#define WorldDB DatabaseFactory::GetInstance()->Get("World")

#endif
