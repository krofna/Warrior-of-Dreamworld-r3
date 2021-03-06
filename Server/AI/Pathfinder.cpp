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
#include "Pathfinder.hpp"
#include "MotionMaster.hpp"
#include "Unit.hpp"
#include "Map.hpp"
#include "Shared/Log.hpp"

#include <stack>

// TODO: Modify below code to work with PERFECTION_LEVEL
// For now it doesnt matter as there are no creatures yet
const int PERFECTION_LEVEL = 32; // Decrease for more "perfect" pathfinding (uses more RAM)
const int MAX_MAP_HEIGHT = std::numeric_limits<uint16>::max() / PERFECTION_LEVEL;
const int MAX_MAP_WIDTH = std::numeric_limits<uint16>::max() / PERFECTION_LEVEL;

void Pathfinder::Initialize()
{
    Pathfinder::CreateInstance();
}

Pathfinder::Pathfinder( ) :
GRAY                  (1),
BLACK                 (2)
{
    pWork = nullptr;
    PathfinderGrid.Allocate(MAX_MAP_WIDTH, MAX_MAP_HEIGHT);
    for (uint16 y = 0 ; y < MAX_MAP_HEIGHT ; ++y)
    {
        for (uint16 x = 0 ; x < MAX_MAP_WIDTH ; ++x)
        {
            PathfinderGrid.At(x, y)->Reset();
            PathfinderGrid.At(x, y)->Position.x = x;
            PathfinderGrid.At(x, y)->Position.y = y;
        }
    }
}

Pathfinder::~Pathfinder()
{
    WorkMutex.lock();
    while (!WorkQueue.empty())
    {
        pWork = WorkQueue.front();
        WorkQueue.pop();
        delete pWork;
    }
    WorkMutex.unlock();
    PathfinderGrid.Deallocate();
}

void Pathfinder::ResetPathfinderGrid()
{
    for (uint16 y = 0; y < MAX_MAP_HEIGHT; ++y)
        for (uint16 x = 0; x < MAX_MAP_WIDTH; ++x)
            PathfinderGrid.At(x, y)->Reset();
}

void Pathfinder::Enqueue(MotionMaster* pMotionMaster, Vector2<uint16> Origin, Vector2<uint16> Target)
{
    Work* pJob = new Work;
    pJob->pMotionMaster = pMotionMaster;
    pJob->Origin = Origin;
    pJob->Target = Target;
    pJob->pMe = pMotionMaster->pMe;
    WorkMutex.lock();
    WorkQueue.push(pJob);
    WorkMutex.unlock();
}

void Pathfinder::ProcessAll()
{
    while (!WorkQueue.empty())
    {
        WorkMutex.lock();
        pWork = WorkQueue.front();
        WorkQueue.pop();
        WorkMutex.unlock();
        GeneratePath();
        delete pWork;
    }
}

void Pathfinder::Relax(Node* pFirst, Node* pSecond, uint16 Cost)
{
    // Collision check
    Map* pMap = pWork->pMe->GetContainer()->ToMap();
    if (pMap->At(pSecond->Position))
        return;

    if (pSecond->Color < GRAY || pSecond->Cost > pFirst->Cost + Cost)
    {
        pSecond->Cost = pFirst->Cost + Cost;
        pSecond->pParent = pFirst;

        if (pSecond->Color < GRAY) // < GRAY means WHITE
        {
            pSecond->Color = GRAY;
            OpenList.Insert(pSecond);
        }
        else if (pSecond->Color == GRAY)
        {
            OpenList.DecreaseKey(pSecond->i);
        }
    }
}

void Pathfinder::GeneratePath()
{
    std::stack<Vector2<uint16> >* pPath = new std::stack<Vector2<uint16> >;

    Map* pMap = pWork->pMe->GetContainer()->ToMap();
    uint16 SizeX = pMap->GetSize().x * 32;
    uint16 SizeY = pMap->GetSize().y * 32;

    if (GRAY == 0xFFFF)
        ResetPathfinderGrid();

    GRAY += 2;
    BLACK += 2;

    Node* pCurrent = PathfinderGrid.At(pWork->Origin.x, pWork->Origin.y);
    pCurrent->Color = GRAY;
    pCurrent->Cost = 0;

    OpenList.Clear();
    OpenList.Insert(pCurrent);

    while (!OpenList.Empty())
    {
        pCurrent = OpenList.ExtractMin();

        if (pCurrent->Position == pWork->Target)
        {
            pPath->push(pCurrent->Position);
            while (pCurrent->pParent->pParent)
            {
                pPath->push(pCurrent->pParent->Position);
                pCurrent = pCurrent->pParent;
            }
            pWork->pMotionMaster->PathMutex.lock();
            delete pWork->pMotionMaster->pPath;
            pWork->pMotionMaster->pPath = pPath;
            pWork->pMotionMaster->PathMutex.unlock();
            return;
        }

        // Right
        if (pCurrent->Position.x < SizeX-1)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y, pCurrent->Position.x+1), 10);
        // Low
        if (pCurrent->Position.y < SizeY-1)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y+1, pCurrent->Position.x), 10);
        // Right-low
        if (pCurrent->Position.x < SizeX-1 && pCurrent->Position.y < SizeY-1)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y+1, pCurrent->Position.x+1), 14);
        // Left
        if (pCurrent->Position.x > 0)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y, pCurrent->Position.x-1), 10);
        // High
        if (pCurrent->Position.y > 0)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y-1, pCurrent->Position.x), 10);
        // Left-high
        if (pCurrent->Position.x > 0 && pCurrent->Position.y > 0)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y-1, pCurrent->Position.x-1), 14);
        // Left-low
        if (pCurrent->Position.x > 0 && pCurrent->Position.y < SizeY-1)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y+1, pCurrent->Position.x-1), 14);
        // Right-high
        if (pCurrent->Position.x < SizeX-1 && pCurrent->Position.y > 0)
            Relax(pCurrent, PathfinderGrid.At(pCurrent->Position.y-1, pCurrent->Position.x+1), 14);
        
        pCurrent->Color = BLACK;
    }
    
    delete pPath;
    sLog.Write(LEVEL_WARNING, FILTER_PATHFINDING, "Could not generate path from (%u, %u) to (%u, %u) for unit %u!",
               pWork->Origin.x, pWork->Origin.y, pWork->Target.x, pWork->Target.y, pWork->pMe->GetName());
}
