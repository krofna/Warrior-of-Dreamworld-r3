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
#include "ObjectMgr.hpp"
#include "Database.hpp"

ObjectMgr::~ObjectMgr()
{
    std::for_each(CreatureTemplates.begin(), CreatureTemplates.end(), MapDeleter());
    std::for_each(GameObjectTemplates.begin(), GameObjectTemplates.end(), MapDeleter());
    std::for_each(ItemTemplates.begin(), ItemTemplates.end(), MapDeleter());
    std::for_each(QuestTemplates.begin(), QuestTemplates.end(), MapDeleter());
    std::for_each(SpellTemplates.begin(), SpellTemplates.end(), MapDeleter());
    std::for_each(MapTemplates.begin(), MapTemplates.end(), MapDeleter());
    std::for_each(PlayerTemplates.begin(), PlayerTemplates.end(), MapDeleter());
}

CreatureTemplate* ObjectMgr::GetCreatureTemplate(uint32 Entry) const
{
    auto CTemplate = CreatureTemplates.find(Entry);
    if(CTemplate != CreatureTemplates.end())
        return CTemplate->second;

    return nullptr;
}

GameObjectTemplate* ObjectMgr::GetGameObjectTemplate (uint32 Entry) const
{
    auto CTemplate = GameObjectTemplates.find(Entry);
    if(CTemplate != GameObjectTemplates.end())
        return CTemplate->second;

    return nullptr;
}

ItemTemplate* ObjectMgr::GetItemTemplate(uint32 Entry) const
{
    auto ITemplate = ItemTemplates.find(Entry);
    if (ITemplate != ItemTemplates.end())
        return ITemplate->second;

    return nullptr;
}

SpellTemplate* ObjectMgr::GetSpellTemplate(uint32 Entry) const
{
    auto STemplate = SpellTemplates.find(Entry);
    if (STemplate != SpellTemplates.end())
        return STemplate->second;

    return nullptr;
}

MapTemplate* ObjectMgr::GetMapTemplate(uint32 Entry) const
{
    auto MTemplate = MapTemplates.find(Entry);
    if (MTemplate != MapTemplates.end())
        return MTemplate->second;

    return nullptr;
}

PlayerTemplate* ObjectMgr::GetPlayerTemplate(uint32 Entry) const
{
    auto PTemplate = PlayerTemplates.find(Entry);
    if (PTemplate != PlayerTemplates.end())
        return PTemplate->second;

    return nullptr;
}

WorldObjectQuests ObjectMgr::GetCreatureQuests(uint32 Entry) const
{
    return CreatureQuests.equal_range(Entry);
}

void ObjectMgr::LoadCreatureTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `creature_template`"));

    CreatureTemplate* pTemplate;

    while(Result->next())
    {
        pTemplate = new CreatureTemplate;

        pTemplate->Entry      = Result->getUInt   (1);
        pTemplate->Name       = Result->getString (2);
        pTemplate->Tileset    = Result->getString (3);
        pTemplate->TextureX   = Result->getUInt   (4);
        pTemplate->TextureY   = Result->getUInt   (5);
        pTemplate->Flag       = Result->getUInt   (6);
        pTemplate->MaxHealth  = Result->getUInt   (7);
        pTemplate->MaxPower   = Result->getUInt   (8);
        pTemplate->ScriptName = Result->getString (9);

        CreatureTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadGameObjectTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `gameobject_template`"));

    GameObjectTemplate* pTemplate;

    while(Result->next())
    {
        pTemplate = new GameObjectTemplate;

        pTemplate->Entry      = Result->getUInt   (1);
        pTemplate->Name       = Result->getString (2);
        pTemplate->Tileset    = Result->getString (3);
        pTemplate->TextureX   = Result->getUInt   (4);
        pTemplate->TextureY   = Result->getUInt   (5);
        pTemplate->Flag       = Result->getUInt   (6);
        pTemplate->ScriptName = Result->getString (7);

        GameObjectTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadItemTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `item_template`"));

    ItemTemplate* pTemplate;

    while (Result->next())
    {
        pTemplate = new ItemTemplate;

        pTemplate->Entry          = Result->getUInt   (1);
        pTemplate->Name           = Result->getString (2);
        pTemplate->Class          = Result->getUInt   (3);
        pTemplate->Tileset        = Result->getString (4);
        pTemplate->TextureX       = Result->getUInt   (5);
        pTemplate->TextureY       = Result->getUInt   (6);
        pTemplate->InventoryType  = Result->getUInt   (7);
        pTemplate->ContainerSlots = Result->getUInt   (8);
        pTemplate->Description    = Result->getString (9);

        ItemTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadQuestTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `quest_template`"));
    
    QuestTemplate* pTemplate;
    
    while (Result->next())
    {
        pTemplate = new QuestTemplate;
        
        pTemplate->Entry     = Result->getUInt   (1);
        pTemplate->Title     = Result->getString (2);
        pTemplate->Details   = Result->getString (3);
        pTemplate->Objective = Result->getString (4);
        
        QuestTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadSpellTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `spell_template`"));

    SpellTemplate* pTemplate;

    while (Result->next())
    {
        pTemplate = new SpellTemplate;

        pTemplate->Entry     = Result->getUInt   (1);
        pTemplate->Name      = Result->getString (2);
        pTemplate->Tileset   = Result->getString (3);
        pTemplate->TextureX  = Result->getUInt   (4);
        pTemplate->TextureY  = Result->getUInt   (5);
        pTemplate->Flag      = Result->getUInt   (6);
        pTemplate->BaseValue = Result->getUInt   (7);
        pTemplate->BaseCost  = Result->getUInt   (8);

        SpellTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadMapTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `map_template`"));

    MapTemplate* pTemplate;

    while (Result->next())
    {
        pTemplate = new MapTemplate;

        pTemplate->Entry      = Result->getUInt   (1);
        pTemplate->Width      = Result->getUInt   (2);
        pTemplate->Height     = Result->getUInt   (3);
        pTemplate->Flag       = Result->getUInt   (4);
        pTemplate->ScriptName = Result->getString (5);

        MapTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadPlayerTemplates()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `player_template`"));

    PlayerTemplate* pTemplate;

    while (Result->next())
    {
        pTemplate = new PlayerTemplate;

        pTemplate->Entry      = Result->getUInt   (1);
        pTemplate->Class      = Result->getString (2);
        pTemplate->Tileset    = Result->getString (3);
        pTemplate->TextureX   = Result->getUInt   (4);
        pTemplate->TextureY   = Result->getUInt   (5);

        PlayerTemplates[pTemplate->Entry] = pTemplate;
    }
}

void ObjectMgr::LoadCreatureQuests()
{
    QueryResult Result(WorldDB->Query("SELECT * FROM `creature_quest`"));
    
    while (Result->next())
    {
        CreatureQuests.insert(std::pair<uint32, uint32>(Result->getUInt(1), Result->getUInt(2)));
    }
}
