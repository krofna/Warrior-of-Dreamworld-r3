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
#ifndef MOTION_MASTER_HPP
#define MOTION_MASTER_HPP

#include "Shared/BasicTypes.hpp"
#include "Shared/Vector2.hpp"

#include <stack>
#include <mutex>

class Unit;

enum MotionType
{
    MOTION_STOP         = 0,
    MOTION_MOVE_POINT   = 1,
    MOTION_CHASE        = 2
};

class MotionMaster
{
    friend class Pathfinder;
public:
    explicit MotionMaster(Unit* pMe);
    ~MotionMaster();

    void Update(uint32 diff);
private:
    std::stack<Vector2<uint16> >* pPath;
    std::mutex PathMutex;
    uint8 MotionStatus;
    Unit* pMe;
};

#endif
