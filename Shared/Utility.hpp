/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2012-2013 Mislav Blazevic, Ryan Lahfa

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
#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <boost/format.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/lexical_cast.hpp>

extern boost::random::mt19937 Generator;

struct MapDeleter
{
    template <class T>
    void operator() (T Data)
    {
        delete Data.second;
    }
};

struct Deleter
{
    template <class T>
    void operator() (T Data)
    {
        delete Data;
    }
};

template<class T>
inline std::string ToString(T What)
{
    return boost::lexical_cast<std::string>(What);
}

inline int urand(int Min, int Max)
{
    boost::random::uniform_int_distribution<> Dist(Min, Max);
    return Dist(Generator);
}

inline std::string Format(boost::format& formater)
{
    return formater.str();
}

inline std::string Format(std::string const& ToFormat)
{
    return ToFormat;
}

template<typename T, typename... Values>
inline std::string Format(boost::format& formater, T const& Val, Values... Vals)
{
    return Format(formater % Val, std::forward<Values>(Vals)...);
}

template<typename T, typename... Values>
inline std::string Format(std::string const& ToFormat, T const& Val, Values... Vals)
{
    return Format(boost::format(ToFormat) % Val, std::forward<Values>(Vals)...);
}

#endif
