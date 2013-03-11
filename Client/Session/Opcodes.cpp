/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2013 Mislav Blazevic, Ryan Lahfa

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
#include "Shared/Opcodes.hpp"

#ifndef MSVC
    #include "WorldSession.hpp"
#endif

OpcodeHandler OpcodeTable[MSG_COUNT] = 
{
    { "MSG_NULL",               &WorldSession::HandleNULL },
    { "MSG_PUBKEY",             &WorldSession::HandlePubkeyOpcode },
    { "MSG_LOGIN",              &WorldSession::HandleLoginOpcode },
    { "SMSG_ADD_OBJECT",        &WorldSession::HandleAddObjectOpcode },
    { "SMSG_REMOVE_OBJECT",     &WorldSession::HandleRemoveObjectOpcode },
    { "SMSG_RELOCATE_OBJECT",   &WorldSession::HandleRelocateObjectOpcode },
    { "SMSG_UPDATE_OBJECT",     &WorldSession::HandleUpdateObjectOpcode }
};
