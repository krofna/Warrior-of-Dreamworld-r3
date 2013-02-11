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
#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include "Shared/Log.hpp"
#include "LogFilter.hpp"

#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>

struct ChatCommand;
class Player;

enum
{
    SEC_PLAYER    = 0,
    SEC_MOD       = 1,
    SEC_DEV       = 2,
    SEC_ADMIN     = 3,
    SEC_CONSOLE   = 4
};

class CommandHandler
{
public:
    CommandHandler(std::string& Msg) : Console(true), Tokenizer(Msg), TokIter(Tokenizer.begin()), pPlayer(nullptr) { }
    CommandHandler(Player* pPlayer, std::string Msg) : pPlayer(pPlayer), Console(false), Tokenizer(Msg), TokIter(Tokenizer.begin()) { }

    // @return: true if command was executed
    //          false if its not a command
    // @throws: BadCommand
    bool ExecuteCommand();

private:
    ChatCommand* GetCommandTable();

    // Handlers
    void HandleAccountCreateCommand();
    void HandleAccountDeleteCommand();
    void HandleAccountSetSecLevelCommand();
    void HandleAccountSetPasswordCommand();

    void HandleKillCommand();

    void HandleTeleportToCommand();
    void HandleTeleportAtCommand();
    void HandleBringCommand();

    void HandleShutdownCommand();
    void HandleGpsCommand();

    void HandleHelpCommand();
    ChatCommand* SubCommandHelper(std::string const& BaseCommand);

    bool IsEndArgument() const;

    template <class T>
    void ExtractArg(T& Arg);
//    #if defined(HAS_VARIADIC_TEMPLATE)
//        template<class T, class... Tn>
//        void ExtractArgs(T& Arg, Tn&... Arg);
//  #endif

    Player* pPlayer;
    boost::tokenizer<> Tokenizer;
    boost::tokenizer<>::iterator TokIter;
    bool Console;

public:
    class BadCommand {};
};

template<>
void CommandHandler::ExtractArg<std::string>(std::string& Arg);

template <class T>
void CommandHandler::ExtractArg(T& Arg)
{
    try
    {
        std::string TempArg;
        ExtractArg(TempArg);
        Arg = boost::lexical_cast<T>(TempArg);
    }
    catch (boost::bad_lexical_cast& e)
    {
        sLog.Write(LEVEL_ERROR, LOG_COMMANDS, e.what());
        throw BadCommand();
    }
}

//#if defined(HAS_VARIADIC_TEMPLATE)
//    template<>
//    void CommandHandler::ExtractArg<>() { }
//
//    template<class T, class... Tn>
//    void CommandHandler::ExtractArgs(T& Arg, Tn&... Args)
//    {
//        ExtractArg(Arg);
//        ExtractArgs(std::forward<Tn>(Args)...);
//    }
//#endif

#include <string>

struct ChatCommand
{
    const char* Name;
    uint8 SecurityLevel;
    bool AllowConsole;
    void (CommandHandler::*Handler)();
    std::string Help;
    ChatCommand* ChildCommands;
};

#endif
