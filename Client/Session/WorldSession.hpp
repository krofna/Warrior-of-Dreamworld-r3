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
#ifndef WORLD_SESSION_HPP
#define WORLD_SESSION_HPP

#include "Shared/WorldPacket.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>

typedef boost::asio::ip::tcp::socket TCPSocket;
typedef boost::asio::ip::tcp::resolver TCPResolver;

class WorldSession : public boost::enable_shared_from_this<WorldSession>
{
public:
    WorldSession(boost::asio::io_service& io);
    ~WorldSession();

    void Start();
    void Send(WorldPacket& Packet);

    // Opcode handlers
    void HandleNULL();
    void HandlePubkeyOpcode();
    void HandleLoginOpcode();
    void HandleAddObjectOpcode();
    void HandleRemoveObjectOpcode();
    void HandleRelocateObjectOpcode();
    void HandleUpdateObjectOpcode();
private:
    void HandleSend(const boost::system::error_code& Error);
    void HandleReceive(const boost::system::error_code& Error);
    void HandleHeader(const boost::system::error_code& Error);

    WorldPacket Packet;
    TCPSocket Socket;
    TCPResolver Resolver;
    std::queue<WorldPacket> MessageQueue;
};

#endif
