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
#include "CreatureAI.hpp" // Krofna has written here : #include "CreatureAI.cpp", I think that it's your most epic fail of your whole life :P
#include "Creature.hpp"

CreatureAI::CreatureAI(Creature* pCreature) :
AI                    (pCreature)
{
}

CreatureAI::~CreatureAI()
{
}

void CreatureAI::UpdateAI(uint32 diff)
{
    if (!pMe->GetVictim())
        return;
    
    DoMeleeAttackIfReady();
}

void CreatureAI::DoMeleeAttackIfReady()
{
}
