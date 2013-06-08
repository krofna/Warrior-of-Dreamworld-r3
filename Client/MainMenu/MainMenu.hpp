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
#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

#include <SFGUI/SFGUI.hpp>
#include "Window.hpp"
#include "GameState.hpp"
/*
 * TODO:
 * Load placeholder image in background and render immovable
 * sfgui login screen. Should inherit from generic GameState (need better name)
 * and will be handled in similar way we handled it in original WoD,
 * but this time in Main.
 * @Krofna will deal with abstract design and @OzVessalius should fill in
 * implementations of MainMenu functions
 * */
class MainMenu : public GameState
{
    public:
        virtual ~MainMenu();
        void HandleEvent(sf::Event Event);
        void Update();
        void Draw();        
    
    private:
        void Create();
        void onConnectButtonPressed();

    private:
        sfg::Window::Ptr m_MainMenuWin;
        sfg::Label::Ptr m_ServerLabel;
        sfg::Label::Ptr m_UsernameLabel;
        sfg::Label::Ptr m_PasswordLabel;

        sfg::Entry::Ptr m_ServerEntry;
        sfg::Entry::Ptr m_UsernameEntry;
        sfg::Entry::Ptr m_PasswordEntry;

        sfg::Button::Ptr m_ConnectButton;

        sf::Clock UpdateClock;

};

#endif
