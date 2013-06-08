/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic

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
#ifndef VECTOR2_HPP
#define VECTOR2_HPP

template <class T>
struct Vector2
{
    Vector2();
    Vector2(T x, T y);

    bool operator==(const Vector2<T>& Other);
    bool operator!=(Vector2<T>& Other);
    void operator=(Vector2<T> New);
    template<typename U>
    void operator=(Vector2<U> New)
    {
        x = New.x;
        y = New.y;
    }

    T x;
    T y;
};

template <class T>
Vector2<T>::Vector2()
{
}

template <class T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y)
{
}

template <class T>
bool Vector2<T>::operator==(const Vector2<T>& Other)
{
    return (Other.x == this->x) && (Other.y == this->y);
}

template <class T>
bool Vector2<T>::operator!=(Vector2<T>& Other)
{
    return !(*this == Other);
}

template <class T>
void Vector2<T>::operator=(Vector2<T> New)
{
    this->x = New.x;
    this->y = New.y;
}

#endif
