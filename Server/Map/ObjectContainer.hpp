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
#ifndef OBJECT_CONTAINER_HPP
#define OBJECT_CONTAINER_HPP

#include "Shared/Grid.hpp"

class ObjectContainer : public Grid<Object>
{
public:
    ObjectContainer() : ObjectUpdateGUID(static_cast<uint64>(-1)) { }

    template <class T> void ObjectUpdateField(uint8 Field, T Data);

    virtual void SendUpdate(WorldSession* pSession);
private:
    uint64 ObjectUpdateGUID;
    WorldPacket ObjectUpdatePckt;
};

template <class T>
void ObjectContainer::ObjectUpdateField<T>(uint64 GUID, uint8 Field, T Data)
{
    if (ObjectUpdateGUID != GUID)
    {
        ObjectUpdateGUID = GUID;
        WorldPacket << GUID << uint8(0);
    }
    uint8* FieldNumPtr = ObjectUpdatePckt.GetDataWithoutHeader() + ObjectUpdatePckt.GetSizeWithoutHeader() - sizeof(uint8);
    (*FieldNumPtr)++;
    ObjectUpdatePckt << Field << Data;
}

void ObjectContainer::SendUpdate(WorldSession* pSession)
{
    pSession->Send(ObjectUpdatePckt);
}


#endif
