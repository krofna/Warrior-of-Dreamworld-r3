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
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Shared/Vector2.hpp"
#include "Shared/Templates.hpp"
#include "Shared/ObjectHolder.hpp"
#include "Database.hpp"

class ObjectContainer;

enum TypeMask
{
    TYPE_OBJECT            = 0,
    TYPE_WORLD_OBJECT   = TYPE_OBJECT       | 1,
    TYPE_VEHICLE        = TYPE_WORLD_OBJECT | 2,
    TYPE_GAME_OBJECT    = TYPE_WORLD_OBJECT | 4,
    TYPE_UNIT           = TYPE_WORLD_OBJECT | 8,
    TYPE_CREATURE       = TYPE_UNIT         | 16,
    TYPE_PET            = TYPE_CREATURE     | 32,
    TYPE_PLAYER         = TYPE_UNIT         | 64,
    TYPE_ITEM           = TYPE_OBJECT       | 128
};

enum UpdateObjectField
{
    FIELD_POS_X         = 1, // uint16
    FIELD_POS_Y         = 2, // uint16
    FIELD_IS_IN_WORLD   = 3, // bool: false => destroy
};

template <typename T>
class GenericObjectFactory
{
    public:
    T* Create(uint32 Entry)
    {
        T* pObject = new T;
        pObject->Create(Entry);
        ObjectHolder<T>::Insert(pObject);
        return pObject;
    }

    T* Load(QueryResult& Result)
    {
        T* pObject = new T(Result);
        pObject->Create(Result->getUInt(2));
        ObjectHolder<T>::Insert(pObject);
        return pObject;
    }
};

#define DEFINE_GENERIC_OBJECT_FACTORY(X) struct Factory : public GenericObjectFactory<X> \
                                         { };

class Object
{
    DEFINE_GENERIC_OBJECT_FACTORY(Object)
public:
    virtual ~Object() = 0;

    virtual void Update(uint32 diff);

    std::string GetName() const;
    uint64 GetGUID() const;
    Vector2<uint16> GetPosition() const;
    ObjectContainer* GetContainer();

    void Relocate(Vector2<uint16>& Where);

protected:
    Object(QueryResult& Result);
    virtual void Create(uint32 Entry) = 0;

    uint8 ObjectMask;
    uint64 GUID;
    std::string Name;
    ObjectContainer* pContainer;
    ObjectTemplate* pTemplate;
    Vector2<uint16> Pos;
};

#endif
