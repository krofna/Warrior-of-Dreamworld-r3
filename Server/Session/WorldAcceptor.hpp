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
#ifndef WORLD_ACCEPTOR_HPP
#define WORLD_ACCEPTOR_HPP

#include "Shared/Opcodes.hpp"
#include "Shared/Singleton.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

typedef boost::asio::ip::tcp::endpoint TCPEndpoint;
typedef boost::asio::ip::tcp::acceptor TCPAcceptor;
typedef std::unique_ptr<TCPAcceptor> TCPAcceptorPtr;
typedef std::shared_ptr<WorldSession> WorldSessionPtr;

class WorldAcceptor : public Singleton
{
public:
    WorldAcceptor(boost::asio::io_service& io);

    void Accept();
private:
    void HandleAccept(const boost::system::error_code& Error);

    TCPAcceptorPtr Acceptor;
    TCPEndpoint Endpoint;
    WorldSessionPtr NewSession;
};

#endif
