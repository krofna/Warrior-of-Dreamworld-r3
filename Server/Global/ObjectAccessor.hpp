/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2013 Mislav Blazevic, Ryan Lahfa

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
#ifndef OBJECT_ACCESSOR_HPP
#define OBJECT_ACCESSOR_HPP

#include "Shared/ObjectHolder.hpp"
#include "Shared/Singleton.hpp"
#include "PlayerHolder.hpp"

class Player;
class Creature;
class GameObject;
class Map;

class ObjectAccessor : public Singleton<ObjectAccessor>
{
    friend class Singleton<ObjectAccessor>;
    ObjectAccessor() = default;
public:    
    Player* FindPlayer(uint64 GUID)                 { return FindObjectInWorld<Player>(GUID);       }
    Player* FindPlayer(std::string const& Username) { return ObjectHolder<Player>::Find(Username);  }

    Creature* FindCreature(uint64 GUID)             { return FindObjectInWorld<Creature>(GUID);     }

    Map* FindMap(uint64 GUID)                       { return FindObjectInWorld<Map>(GUID);         }

    template <class T>
    T* FindObjectInWorld(uint64 GUID)               { return ObjectHolder<T>::Find(GUID);           }
};

#endif
