/*
   Warrior of Dreamworld, 2D Massively Mutiplayer Online Role-playing Game
   Copyright (C) 2012-2013 Ryan Lahfa (OzVessalius)

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

#include "Shared/Singleton.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <map>

class ObjectMgr : public Singleton<ObjectMgr>
{
    friend class Singleton<ObjectMgr>;
    ObjectMgr();

    public:
    sf::Texture* GetTileset(std::string const& Filename);

    private:
    std::map<std::string, sf::Texture* > m_Textures;
};
