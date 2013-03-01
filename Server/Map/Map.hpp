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
#ifndef MAP_HPP
#define MAP_HPP

#include "WorldObject.hpp"
#include "ObjectContainer.hpp"

class Map : public ObjectContainer
{
public:
    Map();
    
    // Updates map. Called on every server thick
    virtual void Update(uint32 diff);
    
    // Enqueues packet which is to be sent to players in map
    void EnqueuePlayerUpdate(WorldPacket& Data);
    
    // Actually sends packets to pSession
    virtual void SendUpdate(WorldSession* pSession);

    // TODO: ??
    uint64 GetGUID() { return m_GUID; }
protected:
    // Packets enqueued by EnqueuePlayerUpdate and sent in SendUpdate
    std::vector<WorldPacket> PacketsForPlayers;
    uint64 m_GUID;
};

#endif
