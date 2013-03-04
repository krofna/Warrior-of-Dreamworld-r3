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
#ifndef GRID_HPP
#define GRID_HPP

#include "Shared/Vector2.hpp"
#include "Shared/BasicTypes.hpp"

#include <vector>
#include <mutex>

template <class T>
class Grid
{
public:
    T* At(Vector2<uint16> const& Pos);
    T* At(uint16 x, uint16 y);
    void Resize(uint16 x, uint16 y);
    void Remove(Vector2<uint16> const& Pos);
    void Insert(T* What);
    Vector2<uint16> GetSize();
    uint16 GetSizeX();
    uint16 GetSizeY();

private:
    Vector2<uint16> Size;
    std::vector<T*> Array;
    std::mutex ArrayMutex;
};

template <class T>
T* Grid<T>::At(Vector2<uint16> const& Pos)
{
    std::lock_guard<std::mutex> Lock(ArrayMutex);
    return Array[Size.y * Pos.y + Pos.x];
}

template <class T>
T* Grid<T>::At(uint16 x, uint16 y)
{
    std::lock_guard<std::mutex> Lock(ArrayMutex);
    return Array[Size.y * y + x];
}

template <class T>
void Grid<T>::Resize(uint16 x, uint16 y)
{
    Size.x = x;
    Size.y = y;
    Array.resize(x * y);
}

template <class T>
Vector2<uint16> Grid<T>::GetSize()
{
    return Size;
}

template <class T>
uint16 Grid<T>::GetSizeX()
{
    return Size.x;
}

template <class T>
uint16 Grid<T>::GetSizeY()
{
    return Size.y;
}

template <class T>
void Grid<T>::Remove(Vector2<uint16> const& Pos)
{
    Array[Size.y * Pos.y + Pos.x] = nullptr;
}

template <class T>
void Grid<T>::Insert(T* What)
{
    Array[Size.y * What->GetPosition().y + What->GetPosition().x] = What;
}

#endif
