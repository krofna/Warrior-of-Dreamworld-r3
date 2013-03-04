#ifndef PLAYER_HOLDER_HPP
#define PLAYER_HOLDER_HPP

#include "Player.hpp"
#include "Shared/ObjectHolder.hpp"
#include "ObjectContainer.hpp"

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
    static void Execute(F Function)
    {
        for (auto Iter = PlayerMap.begin() ; Iter != PlayerMap.end() ; ++Iter)
        {
            Function((*Iter).second);
        }
    }
private:
    ObjectHolder();
    static std::unordered_map<std::string, Player*> TranscriptionTableUsername;
    static std::unordered_map<uint64, Player* > PlayerMap;
};



#endif
