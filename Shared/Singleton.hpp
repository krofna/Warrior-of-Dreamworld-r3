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

template <class Class>
class Singleton
{
public:
    static Class* GetInstance()
    {
        return sInstance;
    }

    template <typename... Args>
    static void CreateInstance(Args const && ... args)
    {
        if (sInstance != nullptr)
            return;

        sInstance = new Class(std::forward<Args>(args)...);
    }

    static void DestroyInstance()
    {
        if (sInstance)
        {
            delete sInstance;
            sInstance = nullptr;
        }
    }

protected:
    Singleton() = default;

    Singleton(const Singleton<Class>& Other) = delete;
    Singleton(const Singleton<Class>&& Other) = delete;
    Singleton& operator =(const Singleton<Class>& Other) = delete;

    ~Singleton() = default;

private:
    static Class* sInstance;
};

template <class Class>
Class* Singleton<Class>::sInstance = nullptr;

#endif
