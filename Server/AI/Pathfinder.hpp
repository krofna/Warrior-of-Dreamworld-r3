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
#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "Shared/Grid.hpp"
#include "Shared/Singleton.hpp"
#include "Shared/Vector2.hpp"

#include <queue>
#include <mutex>

class MotionMaster;
class Unit;

class Pathfinder : public Singleton<Pathfinder>
{
    friend class Singleton;

public:
    static void Initialize();
    ~Pathfinder();

    void Enqueue(MotionMaster* pMotionMaster, Vector2<uint16> Origin, Vector2<uint16> Target);
    void ProcessAll();
    void GeneratePath();

    struct Node
    {
        void Reset();

        Vector2<uint16> Position;
        Node* pParent;
        uint16 Cost;
        uint16 Color;
    };

private:
    Pathfinder();

    void ResetPathfinderGrid();
    void Relax(Node* pFirst, Node* pSecond, uint16 Cost, std::priority_queue<Node*>& OpenList);

    struct Work
    {
        Unit* pMe;
        MotionMaster* pMotionMaster;
        Vector2<uint16> Origin;
        Vector2<uint16> Target;
    };
    Work* pWork;
    std::queue<Work*> WorkQueue;
    std::mutex WorkMutex;
    
    /* 1)
     * OLDWHITE  OLDGRAY   OLDBLACK  <-- WHITE |GRAY  BLACK ...
     * 0,        1,        2,        <-- WHITE |3,    4,    ...
    */
    uint16 WHITE, GRAY, BLACK;
    Grid<Node> PathfinderGrid;
};

#endif
