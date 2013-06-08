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

#include <functional>
#include <queue>
#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

class HandlerPriorityQueue
{
    public:
        HandlerQueue();

        void AddHandler(int PriorityLevel, std::function<void ()> Function)
        {
            Handlers.push(QueuedHandler(PriorityLevel, Function));
        }

        void ExecuteAll()
        {
            while (!Handlers.empty())
            {
                QueuedHandler Handler = Handlers.top();
                Handler.Execute();
                Handlers.pop();
            }
        }

        template <typename Handler>
        class WrappedHandler
        {
            public:
                WrappedHandler(HandlerPriorityQueue& queue, int priority, Handler handler) : m_Queue(queue), m_Priority(priority), m_Handler(handler)
                {
                }

                void operator()()
                {
                    m_Handler();
                }

                template <typename... Args>
                void operator()(Args&& ... args)
                {
                    m_Handler(std::forward<Args>(args)...);
                }

                HandlerPriorityQueue& m_Queue;
                int m_Priority;
                Handler m_Handler;
        };

        template <typename Handler>
        WrappedHandler<Handler> Wrap(int Priority, Handler handler)
        {
            return WrappedHandler<Handler>(*this, Priority, handler);
        }

    private:
        class QueuedHandler
        {
            public:
                QueueHandler(int Priority, std::function<void ()> Function) : m_Priority(Priority), m_Function(Function)
                {
                }

                void Execute()
                {
                    m_Function();
                }

                friend bool operator <(QueuedHandler const& A, QueuedHandler const& B)
                {
                    return A.m_Priority < B.m_Priority;
                }
            private:
                int m_Priority;
                std::function<void() > m_Function;

        };
    
    std::priority_queue<QueuedHandler> Handlers;

};

template <typename Function, typename Handler>
void asio_handler_invoke(Function f, QueuedHandler::WrappedHandler<Handler>* h)
{
    h->m_Queue.AddHandler(h->m_Priority, f);
}
