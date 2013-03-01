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
#include "Object.hpp"
#include "ObjectAccessor.hpp"
#include "ObjectContainer.hpp"

Object::Object(QueryResult& Result)
{
    GUID = Result->getUInt64(1);
    Create(Result->getUint(2));
    pContainer = ObjectAccessor::GetInstance()->FindMap(Result->getUInt64(3));
    Pos.x = Result->getUInt(4);
    Pos.y = Result->getUInt(5);
}

uint64 Object::GetGUID() const
{
    return GUID;
}

std::string Object::GetName() const
{
    return Name;
}

Vector2<uint16> Object::GetPosition() const
{
    return Pos;
}

ObjectContainer* Object::GetContainer()
{
    return pContainer;
}

void Object::Relocate(Vector2<uint16>& Where)
{
    Pos = Where;
    pContainer->AppendObjectUpdate(GUID, FIELD_POS_X, Pos.x);
    pContainer->AppendObjectUpdate(GUID, FIELD_POS_Y, Pos.y);
}
