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
#include "NodeQueue.hpp"
#include "Pathfinder.hpp"

#include <utility>

NodeQueue::NodeQueue()
{
    Clear();
}

bool NodeQueue::Empty()
{
    return Size == 0;
}

void NodeQueue::Clear()
{
    Size = 0;
}

void NodeQueue::Insert(Node* pNode)
{
    if (Size <= A.size())
        A.push_back(pNode);
    else
        A[Size] = pNode;
    
    pNode->i = Size++;

    DecreaseKey(Size);
}

void NodeQueue::DecreaseKey(size_t i)
{
    while (i > 0 && A[Parent(i)]->Cost > A[i]->Cost)
    {
        std::swap(A[Parent(i)]->i, A[i]->i);
        std::swap(A[Parent(i)], A[i]);
        i = Parent(i);
    }
}

Node* NodeQueue::ExtractMin()
{
    if (Size == 0)
        return nullptr;

    Node* Min = A[0];
    A[0] = A[--Size];
    A[0]->i = 0;
    Heapify(0);

    return Min;
}

void NodeQueue::Heapify(size_t i)
{
    size_t l = Left(i);
    size_t r = Right(i);
    size_t min;

    if (l < Size && A[l]->Cost < A[i]->Cost)
        min = l;
    else
        min = i;
    if (r < Size && A[r]->Cost < A[min]->Cost)
        min = r;
    if (min != i)
    {
        std::swap(A[i]->i, A[min]->i);
        std::swap(A[i], A[min]);
        Heapify(min);
    }
}
