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
#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include "BasicTypes.hpp"

#include <string>

struct ObjectTemplate
{
    uint32 Entry;
    std::string Name;
    std::string Tileset;
    uint8 TextureX;
    uint8 TextureY;
};

struct WorldObjectTemplate : ObjectTemplate
{
    std::string ScriptName;
    uint16 Flag;
};

struct CreatureTemplate : WorldObjectTemplate
{
    uint32 MaxHealth;
    uint32 MaxPower;
};

struct GameObjectTemplate : WorldObjectTemplate
{
};

struct PlayerTemplate : ObjectTemplate
{
    std::string Class;
};

struct ItemTemplate : ObjectTemplate
{
    uint32 Class;
    uint32 DisplayInfoID;
    uint32 InventoryType;
    std::string Description;
    uint8 ContainerSlots;
};

struct QuestTemplate
{
    uint32 Entry;
    std::string Title;
    std::string Details;
    std::string Objective;
};

// Weird inheritance, but OK unless we change WorldObjectTemplate
struct SpellTemplate : WorldObjectTemplate
{
    uint32 BaseValue;
    uint32 BaseCost;
};

struct MapTemplate
{
    uint32 Entry;
    std::string Name;
    uint16 Width;
    uint16 Height;
    uint8 Flag;
    std::string ScriptName;
};

enum CreatureFlag
{
    NPC_QUEST_GIVER = 1,
    NPC_VENDOR      = 2,
    NPC_REPAIR      = 4,
    NPC_CHAT        = 8
};

enum GameObjectFlag
{
    GO_GATHERABLE   = 1
};

enum MapFlag
{
    MAP_INSTANCED   = 1
};

enum SpellFlag
{
    SPELL_BOLT      = 1,
    SPELL_CONE      = 2
};


enum InventoryType
{
    INVTYPE_NON_EQUIP,
    INVTYPE_BAG
};

#endif
