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
#include "Map.hpp"
#include "Shared/ObjectHolder.hpp"

Map* Map::Factory::Load(QueryResult Result)
{
    // TODO: Do Something With Result
    return nullptr;
}

Map::Map()
{
    PacketsForPlayers.reserve(10); // Not sure if 10 is a good magic number
}

void Map::Update(uint32 diff)
{
}

void Map::EnqueuePlayerUpdate(WorldPacket& Data)
{
    PacketsForPlayers.push_back(Data);
}

void Map::SendUpdate(WorldSession* pSession)
{
    ObjectContainer::SendUpdate(pSession);
    std::for_each(PacketsForPlayers.begin(), PacketsForPlayers.end(), boost::bind(&WorldSession::Send, pSession, _1));
}
