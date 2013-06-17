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
#ifndef OBJECT_HOLDER_HPP
#define OBJECT_HOLDER_HPP

#include "Shared/BasicTypes.hpp"

#include <unordered_map>
#include <algorithm>

template <class T>
class ObjectHolder
{
public:
    static void Insert(T* pObject);
    static void Erase(T* pObject);
    static T* Find(uint64 GUID);
    
    template <class F>
    static void Execute(F Function)
    {
        for (auto Iter = ObjectMap.begin() ; Iter != ObjectMap.end() ; ++Iter)
        {
            Function((*Iter).second);
        }
    }

private:
    ObjectHolder() {}
    static std::unordered_map<uint64, T*> ObjectMap;
};

template <class T>
std::unordered_map<uint64, T*> ObjectHolder<T>::ObjectMap;

template <class T> void ObjectHolder<T>::Insert(T* pObject)
{
    pObject->GetContainer()->Insert(pObject);
    ObjectMap[pObject->GetGUID()] = pObject;
}

template <class T> void ObjectHolder<T>::Erase(T* pObject)
{
    pObject->GetContainer()->Remove(pObject);
    ObjectMap.erase(pObject->GetGUID());
}

template <class T> T* ObjectHolder<T>::Find(uint64 GUID)
{
    typename std::unordered_map<uint64, T*>::iterator itr = ObjectMap.find(GUID);
    return (itr != ObjectMap.end()) ? itr->second : nullptr;
}

#endif
