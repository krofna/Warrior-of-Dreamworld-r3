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
#ifndef TILE_MAP_HPP
#define TILE_MAP_HPP

#include "Object.hpp"
#include "ObjectMgr.hpp"

#include "Shared/BasicTypes.hpp"
#include "Shared/Grid.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>

/*
 * TODO:
 * Fragment into chunks:
 * a) Draw only chunks which fall into camera view
 * b) Update only objects in chunks which fall into camera view
 * c) Send server screen size so client doesn't get objects which do
 *    not fall int camera view
 * */
class TileMap
{
public:
    // Loads texture
    TileMap(uint16 Entry, bool FullScreen);

    void HandleEvent(sf::Event Event);
    void Draw();

    void RemoveObject(uint64 GUID);
    void AddObject(Object* pObject);

private:
    // Camera stuff
    uint16 MapWidth;
    uint16 MapHeight;
    uint16 CameraLeft;
    uint16 CameraTop;
    uint16 CameraRight;
    uint16 CameraBottom;
    uint8 MoveCamera;
    bool FullScreen; // TODO: Useless, always true?
    sf::View Camera;

    // Tilemap stuff
    sf::RenderStates States;
    sf::VertexArray Map;
    std::map<uint64, Object> MapObjects;
    uint16 MapIter;
};

#endif
