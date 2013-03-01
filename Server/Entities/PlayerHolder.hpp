#ifndef PLAYER_HOLDER_HPP
#define PLAYER_HOLDER_HPP

#include "Player.hpp"
#include "Shared/ObjectHolder.hpp"

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
