/*
    Warrior of Dreamworld, 2D Massivly Mutiplayer Online Role-playing Game
    Copyright (C) 2013 Mislav Blazevic, Ryan Lahfa

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
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include "Shared/Utility.hpp"

#include <unordered_map>
#include <string>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <stdexcept>
#include <boost/any.hpp>

class Factory
{
public:
    ~Factory()
    {
        std::for_each(FactoryRegistry.begin(), FactoryRegistry.end(), MapDeleter());
    }
    
    template <typename Type>
    static void Register(std::string const& TypeId)
    {
        FactoryRegistry[TypeId] = new (typename Type::Factory);
    }

    template <typename Type, typename... Tn>
    static Type* Create(std::string const& TypeId, Tn... Parameters)
    {
        Type* pType = dynamic_cast<Type* >(boost::any_cast<typename Type::Factory *>(FactoryRegistry[TypeId])->Create(std::forward<Tn>(Parameters)...));a
        if (!pType)
            throw std::runtime_error("Failed to create an Object from dynamic casting.");
        return pType;
    }

    template <typename Type, typename... Tn>
    static Type* Load(std::string const& TypeId, Tn... Parameters)
    {
        Type* pType = dynamic_cast<Type* >(boost::any_cast<typename Type::Factory *>(FactoryRegistry[TypeId])->Load(std::forward<Tn>(Parameters)...));
        if (!pType)
            throw std::runtime_error("Failed to load an Object from dynamic casting.");
        return pType;
    }
    
private:
    Factory();

    static std::unordered_map<std::string, boost::any> FactoryRegistry;
};

std::unordered_map<std::string, boost::any> Factory::FactoryRegistry;

#endif
