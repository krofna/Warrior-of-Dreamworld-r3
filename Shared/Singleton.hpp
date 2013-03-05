/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Ryan Lahfa

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
#ifndef SINGLETON_HPP
#define SINGLETON_HPP
#include <functional>
#include <memory>
#include <type_traits>

template <class Class>
class Singleton
{
public:
    static Class* GetInstance()
    {
        return sInstance.get();
    }

    template <typename... Args>
    static void CreateInstance(Args &&... args)
    {
        if (sInstance != nullptr)
            return;

        sInstance.reset(new Class(std::forward<Args>(args)...));
    }

protected:
    Singleton() = default;

    Singleton(const Singleton<Class>& Other) = delete;
    Singleton(const Singleton<Class>&& Other) = delete;
    Singleton& operator =(const Singleton<Class>& Other) = delete;

    ~Singleton() = default;

private:
    static std::unique_ptr<Class> sInstance;
};

template <class Class>
std::unique_ptr<Class> Singleton<Class>::sInstance;

#endif
