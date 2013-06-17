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

#include "Shared/Vector2.hpp"
#include "Shared/WorldPacket.hpp"

class WorldSession;
class Map;
class Object;

// Base class for Bag and Map
class ObjectContainer
{
public:
    ObjectContainer();

    // Appends Data to be updated in Field for GUID object
    template <class T>
    void ObjectUpdateField(uint64 GUID, uint8 Field, T Data);
    
    // Actually sends Object Update
    void SendUpdate(WorldSession* pSession);
    
    // Unsafe downcast
    Map* ToMap() { return (Map*)this; }
    // Bag* ToBag() { return (Bag*)this; }

    // Returns WorldObject at Pos
    virtual Object* At(Vector2<uint16> Pos) = 0;

    // Inserts object into container
    virtual void Insert(Object* pObject) = 0;

    // Removes object from map
    virtual void Remove(Object* pObject) = 0;
    
    Vector2<uint16> GetSize() const;
    
private:
    // Size of the container
    Vector2<uint16> Size;

    // Packet containing Object Updates
    WorldPacket ObjectUpdatePckt;
    
    // Current object appending its fields for update
    uint64 ObjectUpdateGUID;
};

template <class T>
void ObjectContainer::ObjectUpdateField(uint64 GUID, uint8 Field, T Data)
{
    if (ObjectUpdateGUID != GUID)
    {
        ObjectUpdateGUID = GUID;
        ObjectUpdatePckt << GUID << uint8(0); // GUID & Num fields to update for this GUID
    }
    uint8* FieldNumPtr = ObjectUpdatePckt.GetDataWithoutHeader() + ObjectUpdatePckt.GetSizeWithoutHeader() - sizeof(uint8);
    (*FieldNumPtr)++;
    ObjectUpdatePckt << Field << Data;
}

#endif
