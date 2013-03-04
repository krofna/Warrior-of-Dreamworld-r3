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
#ifndef CREATURE_AI_HPP
#define CREATURE_AI_HPP

#include "AI.hpp"

class Unit;
class Creature;

class CreatureAI : public AI<Creature>
{
public:
    struct Factory
    {};
public:
    explicit CreatureAI(Creature* pCreature);
    virtual ~CreatureAI();

    // Called on World::Update
    virtual void UpdateAI(uint32 diff);

    // Called when creature enters combat
    virtual void EnterCombat(Unit* pEnemy){}

    // Called when creature starts leaves combat
    virtual void LeaveCombat(){}

    // Called when creature dies
    virtual void JustDied(Unit* pKiller){}

    // Called when creature kills unit
    virtual void KilledUnit(Unit* pVictim){}

    // Called before creature is hit by melee attack
    virtual void Hit(Unit* pAttacker, int32& Damage){}

    // TODO: Called when creature is hit by spell
    //virtual void SpellHit(){}
    
    void DoMeleeAttackIfReady();
};

#endif
