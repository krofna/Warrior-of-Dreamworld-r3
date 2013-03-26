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
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Shared/Vector2.hpp"
#include "Shared/WorldPacket.hpp"

#include <vector>

// Keep in mind that spells are valid objects as well on client side!
class Object
{
public:
	Object(WorldPacket& Packet);

    uint32 GetWorldX() const   { return WorldPosition.y; }
    uint32 GetWorldY() const   { return WorldPosition.x; }
    uint16 GetTileX() const    { return TilePosition.x;  }
    uint16 GetTileY() const    { return TilePosition.y;  }
    uint16 GetTextureX() const { return TexturePositions[TexPosIter].x }
    uint16 GetTextureY() const { return TexturePositions[TexPosIter].y }
private:
    uint8 TexPosIter; // Current frame (TexturePositions index)
    std::vector<Vector2<uint16> > TexturePositions; // All animation frames
    Vector2<uint16> TilePosition; // Server side position
    Vector2<uint32> WorldPosition; // Actual position (e.g. between 2 tiles)
    uint64 GUID; // Server-side globally unique identifier
    uint32 Entry; // Identifier unique to specific ObjectMask
    uint8 ObjectMask; // Type of the object
    float Speed; // Pixels per second
};

#endif
