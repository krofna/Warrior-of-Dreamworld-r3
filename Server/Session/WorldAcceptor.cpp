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
#include "WorldAcceptor.hpp"
#include "World.hpp"
#include "Shared/Log.hpp"
#include "WorldSession.hpp"
#include "Database.hpp"

#include <boost/asio/placeholders.hpp>
#include <boost/bind.hpp>

WorldAcceptor::WorldAcceptor(boost::asio::io_service& io) :
Endpoint                    (boost::asio::ip::tcp::v4(), 0xBEEF) // Port value = 48879
{
    Acceptor.reset(new TCPAcceptor(io, Endpoint));
}

void WorldAcceptor::HandleAccept(const boost::system::error_code& Error)
{
    if(!Error)
        NewSession->Start();

    Accept();
}

void WorldAcceptor::Accept()
{
    NewSession = std::make_shared<WorldSession>(Acceptor->get_io_service());
    Acceptor->async_accept(NewSession->Socket,
        boost::bind(&WorldAcceptor::HandleAccept, this,
        boost::asio::placeholders::error));
}

