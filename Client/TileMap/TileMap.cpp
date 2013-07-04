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
#include "TileMap.hpp"
#include "Window.hpp"

#include <fstream>

const int TILE_SIZE = 32;

enum
{
    MOVE_STOP   = 0,
    MOVE_UP     = 1,
    MOVE_DOWN   = 2,
    MOVE_LEFT   = 4,
    MOVE_RIGHT  = 8
};

TileMap::TileMap(uint16 Entry, bool FullScreen) :
FullScreen      (FullScreen)
{
    std::string Path = "Data/Maps/Map" + ToString(Entry) + ".map";

    std::ifstream File(Path);
    assert(File);
    
    int index = 0;
    float x, y, tx, ty;

    File >> MapWidth >> MapHeight;
    Map.resize(MapWidth * MapHeight * 4);
    
    std::string TilesetFileName;
    File >> TilesetFileName;

    States.texture = ObjectMgr::GetInstance()->GetTileset(TilesetFileName);

    while (File >> x >> y >> tx >> ty)
    {
        Map[index + 0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
        Map[index + 1].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);
        Map[index + 2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
        Map[index + 3].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);

        Map[index + 0].texCoords = sf::Vector2f(tx * TILE_SIZE, ty * TILE_SIZE);
        Map[index + 1].texCoords = sf::Vector2f(tx * TILE_SIZE, (ty + 1) * TILE_SIZE);
        Map[index + 2].texCoords = sf::Vector2f((tx + 1) * TILE_SIZE, (ty + 1) * TILE_SIZE);
        Map[index + 3].texCoords = sf::Vector2f((tx + 1) * TILE_SIZE, ty * TILE_SIZE);

        index += 4;
    }

    Map.resize((Window::GetInstance()->getSize().x / TILE_SIZE) * (Window::GetInstance()->getSize().y / TILE_SIZE) * 4);
}

void TileMap::HandleEvent(sf::Event Event)
{
    if (FullScreen)
    {
        if (Event.type == sf::Event::MouseMoved)
        {
            MoveCamera = MOVE_STOP;

            if (sf::Mouse::getPosition(*Window::GetInstance()).x >= Window::GetInstance()->getSize().x - (TILE_SIZE / 2))
                MoveCamera |= MOVE_RIGHT;

            else if (sf::Mouse::getPosition(*Window::GetInstance()).x < TILE_SIZE / 2)
                MoveCamera |= MOVE_LEFT;

            if (sf::Mouse::getPosition(*Window::GetInstance()).y > Window::GetInstance()->getSize().y - (TILE_SIZE / 2))
                MoveCamera |= MOVE_DOWN;

            else if (sf::Mouse::getPosition(*Window::GetInstance()).y < TILE_SIZE / 2)
                MoveCamera |= MOVE_UP;
        }
    }
}

void TileMap::Draw()
{
    if (FullScreen)
    {
        if (MoveCamera != MOVE_STOP)
        {
            if (MoveCamera & MOVE_UP && CameraTop > 0)
            {
                --CameraTop;
                --CameraBottom;
                Camera.move(0, -TILE_SIZE);
            }

            else if (MoveCamera & MOVE_DOWN && CameraBottom < MapHeight)
            {
                ++CameraTop;
                ++CameraBottom;
                Camera.move(0, TILE_SIZE);
            }

            if (MoveCamera & MOVE_RIGHT && CameraRight < MapWidth)
            {
                ++CameraLeft;
                ++CameraRight;
                Camera.move(TILE_SIZE, 0);
            }

            else if (MoveCamera & MOVE_LEFT && CameraLeft > 0)
            {
                --CameraLeft;
                --CameraRight;
                Camera.move(-TILE_SIZE, 0);
            }

            Window::GetInstance()->setView(Camera);
        }
    }
    Window::GetInstance()->draw(Map, States);
    //std::for_each(MapObjects.begin(), MapObjects.end(), bind...
}

void TileMap::RemoveObject(uint64 GUID)
{
}

void TileMap::AddObject(Object* pObject)
{
}
