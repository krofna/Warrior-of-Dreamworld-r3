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
#include "WorldSession.hpp"
#include "Shared/Log.hpp"
#include "Shared/Opcodes.hpp"

#include <boost/bind.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/placeholders.hpp>

WorldSession::WorldSession(boost::asio::io_service& io) :
Socket                    (io),
Resolver                  (io)
{
}

WorldSession::~WorldSession()
{
}

void WorldSession::Start()
{
    Packet = WorldPacket((uint16)MSG_NULL);

    boost::asio::async_read(Socket,
        boost::asio::buffer(Packet.GetDataWithHeader(), WorldPacket::HEADER_SIZE),
        boost::bind(&WorldSession::HandleHeader, shared_from_this(), boost::asio::placeholders::error));
}

void WorldSession::HandleHeader(const boost::system::error_code& Error)
{
    Packet.ReadHeader();

    // Header only packet or perhaps an error receiving the header?
    if (Packet.GetSizeWithoutHeader() < 1 || Error)
    {
        HandleReceive(Error);
    }
    else
    {
        boost::asio::async_read(Socket,
            boost::asio::buffer(Packet.GetDataWithoutHeader(), Packet.GetSizeWithoutHeader()),
            boost::bind(&WorldSession::HandleReceive, shared_from_this(), boost::asio::placeholders::error));
    }
}

void WorldSession::HandleReceive(const boost::system::error_code& Error)
{
    Packet.ResetReadPos();

    if (Error)
    {
        sLog.Write(LEVEL_ERROR, FILTER_PACKET, "Failed to receive packet");
    }
    else if (Packet.GetOpcode() >= MSG_COUNT)
    {
        sLog.Write(LEVEL_ERROR, FILTER_PACKET, "Received %u: Bad opcode", Packet.GetOpcode());
    }
    else
    {
        if (Packet.GetOpcode() == MSG_NULL)
            sLog.Write(LEVEL_WARNING, FILTER_PACKET, "Received a MSG_NULL, strange...");
        else
            sLog.Write(LEVEL_INFO, FILTER_PACKET, "Received Packet: %s, ", OpcodeTable[Packet.GetOpcode()].Name);

        (this->*OpcodeTable[Packet.GetOpcode()].Handler)();
        Start();
    }
}

void WorldSession::Send(WorldPacket& Packet)
{
    sLog.Write(LEVEL_INFO, FILTER_PACKET, "Sending Packet: %s, ", OpcodeTable[Packet.GetOpcode()].Name);

    Packet.UpdateSizeData();
    MessageQueue.push(Packet);
    if (MessageQueue.size() == 1)
    {
        boost::asio::async_write(Socket,
            boost::asio::buffer(Packet.GetDataWithHeader(), Packet.GetSizeWithHeader()),
            boost::bind(&WorldSession::HandleSend, shared_from_this(), boost::asio::placeholders::error));
    }
}

void WorldSession::HandleSend(const boost::system::error_code& Error)
{
    if (Error)
    {
        sLog.Write(LEVEL_ERROR, FILTER_PACKET, "Failed to send packet: %s", 
            OpcodeTable[MessageQueue.front().GetOpcode()].Name);
    }

    MessageQueue.pop();
    if(!MessageQueue.empty())
    {
        boost::asio::async_write(Socket,
            boost::asio::buffer(MessageQueue.front().GetDataWithHeader(), MessageQueue.front().GetSizeWithHeader()),
            boost::bind(&WorldSession::HandleSend, shared_from_this(), boost::asio::placeholders::error));
    }
}

void WorldSession::HandleNULL()
{
}

void WorldSession::HandlePubkeyOpcode()
{
}

void WorldSession::HandleLoginOpcode()
{
}

void WorldSession::HandleAddObjectOpcode()
{
    Object* pObject = new Object(Packet);
    Game::GetInstance()->GetTileMap()->AddObject(pObject);
}

void WorldSession::HandleRemoveObjectOpcode()
{
}

void WorldSession::HandleRelocateObjectOpcode()
{
}

void WorldSession::HandleUpdateObjectOpcode()
{
}
