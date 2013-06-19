/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2013 Mislav Blazevic

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
#ifndef HEAP_HPP
#define HEAP_HPP

#include "Shared/Vector2.hpp"
#include "Shared/BasicTypes.hpp"

#include <vector>
#include <cstring>
#include <limits>

struct Node
{
    Node()
    {
        Reset();
    }

    void Reset()
    {
        Color = 0;
    }

    Vector2<uint16> Position;
    Node* pParent;
    uint16 Cost;
    uint16 Color;
    size_t i;
};

class NodeQueue
{
public:
    NodeQueue();
    
    bool Empty();
    void Clear();
    void Insert(Node* pNode);
    void DecreaseKey(size_t i);
    Node* ExtractMin();

private:
    void Heapify(size_t i);

    inline size_t Parent (size_t i) { return (i - 1) / 2; }
    inline size_t Left   (size_t i) { return (i * 2) + 1; }
    inline size_t Right  (size_t i) { return (i * 2) + 2; }
    
    size_t Size;
    std::vector<Node*> A;
};

#endif
