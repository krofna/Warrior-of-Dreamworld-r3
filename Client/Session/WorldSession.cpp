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
#include "Shared/Encryption.hpp"

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
    RecPckt = WorldPacket((uint16)MSG_NULL);

    boost::asio::async_read(Socket,
        boost::asio::buffer(RecPckt.GetDataWithHeader(), WorldPacket::HEADER_SIZE),
        boost::bind(&WorldSession::HandleHeader, shared_from_this(), boost::asio::placeholders::error));
}

void WorldSession::HandleHeader(const boost::system::error_code& Error)
{
    RecPckt.ReadHeader();

    // Header only packet or perhaps an error receiving the header?
    if (RecPckt.GetSizeWithoutHeader() < 1 || Error)
    {
        HandleReceive(Error);
    }
    else
    {
        boost::asio::async_read(Socket,
            boost::asio::buffer(RecPckt.GetDataWithoutHeader(), RecPckt.GetSizeWithoutHeader()),
            boost::bind(&WorldSession::HandleReceive, shared_from_this(), boost::asio::placeholders::error));
    }
}

void WorldSession::HandleReceive(const boost::system::error_code& Error)
{
    RecPckt.ResetReadPos();

    if (Error)
    {
        sLog.Write(LEVEL_ERROR, FILTER_PACKET, "Failed to receive packet");
    }
    else if (RecPckt.GetOpcode() >= MSG_COUNT)
    {
        sLog.Write(LEVEL_ERROR, FILTER_PACKET, "Received %u: Bad opcode", RecPckt.GetOpcode());
    }
    else
    {
        if (RecPckt.GetOpcode() == MSG_NULL)
            sLog.Write(LEVEL_WARNING, FILTER_PACKET, "Received a MSG_NULL, strange...");
        else
            sLog.Write(LEVEL_INFO, FILTER_PACKET, "Received Packet: %s, ", OpcodeTable[RecPckt.GetOpcode()].Name);

        (this->*OpcodeTable[RecPckt.GetOpcode()].Handler)();
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

void WorldSession::HandleCreateMapOpcode()
{
    uint16 Entry;
    RecPckt >> Entry;
}

void WorldSession::HandleAddObjectOpcode()
{
    //Object* pObject = new Object(Packet);
    //Game::GetInstance()->GetTileMap()->AddObject(pObject);
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

void WorldSession::SendLogin(std::string const& Username, std::string const& Password)
{
    std::string Hash = HashSHA512AndEncodeHex(Password);
    WorldPacket LoginPckt(MSG_LOGIN);

    LoginPckt << Username << Hash;

    Send(LoginPckt);
}
