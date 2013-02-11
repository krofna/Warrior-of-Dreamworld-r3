/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic, Ryan Lahfa

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
#ifndef OBJECT_MGR_HPP
#define OBJECT_MGR_HPP

#include "Shared/Templates.hpp"
#include "Shared/Singleton.hpp"

#include <map>
#include <unordered_map>

typedef std::pair<std::multimap<uint32, uint32>::const_iterator, std::multimap<uint32, uint32>::const_iterator> WorldObjectQuests;

class ObjectMgr : public Singleton<ObjectMgr>
{
    friend class Singleton<ObjectMgr>;
    ObjectMgr() = default;
public:
    ~ObjectMgr();

    CreatureTemplate*   GetCreatureTemplate   (uint32 Entry) const;
    GameObjectTemplate* GetGameObjectTemplate (uint32 Entry) const;
    ItemTemplate*       GetItemTemplate       (uint32 Entry) const;
    QuestTemplate*      GetQuestTemplate      (uint32 Entry) const;
    SpellTemplate*      GetSpellTemplate      (uint32 Entry) const;
    MapTemplate*        GetMapTemplate        (uint32 Entry) const;
    PlayerTemplate*     GetPlayerTemplate     (uint32 Entry) const;

    WorldObjectQuests   GetCreatureQuests     (uint32 Entry) const;

    void LoadCreatureTemplates();
    void LoadGameObjectTemplates();
    void LoadItemTemplates();
    void LoadQuestTemplates();
    void LoadSpellTemplates();
    void LoadMapTemplates();
    void LoadPlayerTemplates();

    void LoadCreatureQuests();
private:
    std::unordered_map<uint32, CreatureTemplate*>   CreatureTemplates;
    std::unordered_map<uint32, GameObjectTemplate*> GameObjectTemplates;
    std::unordered_map<uint32, ItemTemplate*>       ItemTemplates;
    std::unordered_map<uint32, QuestTemplate*>      QuestTemplates;
    std::unordered_map<uint32, SpellTemplate*>      SpellTemplates;
    std::unordered_map<uint32, MapTemplate*>        MapTemplates;
    std::unordered_map<uint32, PlayerTemplate*>     PlayerTemplates;

    // <Creature Entry, Quest Entry>
    std::multimap<uint32, uint32>                   CreatureQuests;
};

#endif
