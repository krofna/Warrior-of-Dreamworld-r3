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
#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Unit.hpp"

class Creature : public Unit
{
    DEFINE_GENERIC_OBJECT_FACTORY(Creature)
public:
    void operator delete(void* pCreature);

    virtual void Update(uint32 diff);

protected:
    Creature(QueryResult& Result);
    virtual void Create(uint32 Entry);

private:
};

#endif
