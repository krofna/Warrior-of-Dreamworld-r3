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
#include "ObjectMgr.hpp"

#include <boost/asio/ip/tcp.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <queue>

class Player;

typedef boost::asio::ip::tcp::socket TCPSocket;

class WorldSession : public boost::enable_shared_from_this<WorldSession>
{
    friend class WorldAcceptor;
public:
    WorldSession(boost::asio::io_service& io);
    ~WorldSession();

    void Start();
    void Send(WorldPacket& Packet);

    // Opcode handlers
    void HandleNULL();
    
    Player* GetPlayer();
private:
    void HandleSend(const boost::system::error_code& Error);
    void HandleReceive(const boost::system::error_code& Error);
    void HandleHeader(const boost::system::error_code& Error);

    TCPSocket Socket;
    WorldPacket Packet;
    Player* pPlayer;

    std::queue<WorldPacket> MessageQueue;
};

#endif
