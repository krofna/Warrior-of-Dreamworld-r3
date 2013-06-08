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
#include "Game.hpp"
#include "GameState.hpp"
#include "Window.hpp"

Game::Game()
{
    Window::CreateInstance();
}

Game::~Game()
{
    PopAllStates();
}

void Game::Update()
{
    while (Window::GetInstance()->pollEvent(Event))
        StateStack.top()->HandleEvent(Event);

    Window::GetInstance()->clear();
    StateStack.top()->Draw();
    Window::GetInstance()->display();
    StateStack.top()->Update();
}

void Game::PushState(GameState* pState)
{
    StateStack.push(pState);
}

void Game::PopState()
{
    if (!StateStack.empty())
    {
        delete StateStack.top();
        StateStack.pop();
    }
}

void Game::PopAllStates()
{
    while (!StateStack.empty())
        PopState();
}
