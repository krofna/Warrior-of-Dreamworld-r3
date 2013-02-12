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

class Player : public Unit
{
    DEFINE_GENERIC_OBJECT_FACTORY(Player)
public:
    virtual void Update(uint32 diff);

    // TODO : Fix these functions. Placeholders.
    uint8 GetSecLevel() { return 0; }
    void Kill() { }
    void SendCommandReponse(std::string const& Message) { }
    void Teleport(Map* pMap, Vector2<uint16> const& pos) { }
    void Teleport(Map* pMap, uint16 x, uint16 y) { }
    bool IsInWorld() const { return true; }
    void LogOut() { }
    
    // This will all pending packets to client
    void SendUpdate();

protected:
    Player(uint32 Entry);
    Player(QueryResult& Result);

private:
    WorldSession* pSession;
    Bag* pBackpack;
};

// TODO: This can't be here because of Object.hpp
// FIXME RYAN
template<>
class ObjectHolder<Player>
{
public:
    static void Insert(Player* pPlayer)
    {
        pPlayer->GetContainer()->Insert(pPlayer);
        TranscriptionTableUsername[pPlayer->GetName()] = pPlayer;
        PlayerMap[pPlayer->GetGUID()] = pPlayer;
    }

    static void Erase(Player* pPlayer)
    {
        TranscriptionTableUsername.erase(pPlayer->GetName());
        PlayerMap.erase(pPlayer->GetGUID());
    }

    static Player* Find(uint64 GUID)
    {
        std::unordered_map<uint64, Player*>::iterator It = PlayerMap.find(GUID);
        return (It != PlayerMap.end()) ? It->second : nullptr;
    }

    static Player* Find(std::string const& Username)
    {
        std::unordered_map<std::string, Player*>::iterator It = TranscriptionTableUsername.find(Username);
        return (It != TranscriptionTableUsername.end()) ? It->second : nullptr;
    }

    template <class F>
    void Execute(F Function)
    {
        std::for_each(PlayerMap.begin(), PlayerMap.end(), Function);
    }
private:
    ObjectHolder() { }
    static std::unordered_map<std::string, Player*> TranscriptionTableUsername;
    static std::unordered_map<uint64, Player* > PlayerMap;
};

std::unordered_map<std::string, Player*> ObjectHolder<Player>::TranscriptionTableUsername;
std::unordered_map<uint64, Player*> ObjectHolder<Player>::PlayerMap;

#endif
