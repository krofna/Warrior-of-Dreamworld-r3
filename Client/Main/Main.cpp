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
#include "Game.hpp"
#include "WorldSession.hpp"

Main::Main(boost::asio::io_service& io)
{
    Game::CreateInstance();
    pSession = new WorldSession(io);
}

Main::~Main()
{
    delete pSession;
}

void Main::Load(int argc, char** argv)
{
}

void Main::Run()
{
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
