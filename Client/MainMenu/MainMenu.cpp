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
#include "MainMenu.hpp"

void MainMenu::Create()
{
    m_MainMenuWin = sfg::Window::Create();
    m_MainMenuWin->SetTitle("Main menu");

    sfg::Box::Ptr Global = sfg::Box::Create(sfg::Box::VERTICAL);
    sfg::Box::Ptr IP = sfg::Box::Create(sfg::Box::HORIZONTAL);
    sfg::Box::Ptr Username = sfg::Box::Create(sfg::Box::HORIZONTAL);
    sfg::Box::Ptr Password = sfg::Box::Create(sfg::Box::HORIZONTAL);

    m_ConnectButton = sfg::Button::Create();
    m_ConnectButton->SetLabel("Connect!");

    m_ConnectButton->GetSignal(sfg::Widget::OnLeftClick).Connect(&MainMenu::onConnectButtonPressed, this);

    m_ServerEntry = sfg::Entry::Create();
    m_ServerEntry->SetRequisition(sf::Vector2f(80.f, 0.f));

    m_UsernameEntry = sfg::Entry::Create();
    m_UsernameEntry->SetRequisition(sf::Vector2f(40.f, 0.f));

    m_PasswordEntry = sfg::Entry::Create();
    m_PasswordEntry->SetRequisition(sf::Vector2f(90.f, 0.f));
    m_PasswordEntry->HideText('*');

    IP->Pack(sfg::Label::Create("Server address : "));
    IP->Pack(m_ServerEntry);

    Username->Pack(sfg::Label::Create("Username : "));
    Username->Pack(m_UsernameEntry);

    Password->Pack(sfg::Label::Create("Password : "));
    Password->Pack(m_PasswordEntry);

    Global->Pack(IP);
    Global->Pack(Username);
    Global->Pack(Password);
    Global->Pack(m_ConnectButton);

    Global->SetSpacing(5.f);

    m_MainMenuWin->Add(Global);
    m_MainMenuWin->SetPosition(sf::Vector2f(Window::GetInstance()->getSize().x / 2, Window::GetInstance()->getSize().y / 2));
}

void MainMenu::onConnectButtonPressed()
{
    // WorldSession::GetInstance()->Connect(m_ServerEntry->GetText(), 48879);
    // WorldSession::GetInstance()->SendLogin(m_UsernameEntry->GetText(), m_PasswordEntry->GetText());
}
