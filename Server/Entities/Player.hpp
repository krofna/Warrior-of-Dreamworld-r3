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
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Unit.hpp"
#include "Shared/ObjectHolder.hpp"

class Map;
class WorldSession;

class Player : public Unit
{
    DEFINE_GENERIC_OBJECT_FACTORY(Player)
public:
    virtual void Update(uint32 diff);

    // TODO : Fix these functions. Placeholders.
    uint8 GetSecLevel() { return 0; }
    void Kill() { } // RIP
    void Kick() { } // BOOMO
    void SendCommandReponse(std::string const& Message) { }
    void Teleport(Map* pMap, Vector2<uint16> const pos) { }
    void Teleport(Map* pMap, uint16 x, uint16 y) { }
    bool IsInWorld() const { return true; }
    void LogOut() { }
    
    // This will send all pending packets to client
    void SendUpdate();

protected:
    Player();

private:
    WorldSession* pSession;
};


#endif
