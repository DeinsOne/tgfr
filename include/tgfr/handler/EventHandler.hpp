#ifndef __EVENT_HANDLER_HPP
#define __EVENT_HANDLER_HPP

#include <memory>
#include <tgfr/handler/EventObject.hpp>
#include <tgfr/handler/Event.hpp>
#include <tgfr/manager/EventManager.hpp>

#include <tgbot/Bot.h>

namespace tgfr {

    class EventHandler {
    public:
        EventHandler(const std::shared_ptr<EventManager>& eventmanager) : m_eventmanager(eventmanager) {
        }

        static std::shared_ptr<EventHandler> make_handler(const std::shared_ptr<EventManager>& eventmanager) {
            auto handler = std::make_shared<EventHandler>(eventmanager);
            handler->_impl = handler;
            return handler;
        }

    public:
        template<typename TEvent>
        std::shared_ptr<EventHandler> addEvent() {
            auto event = new TEvent;

            if (auto ptr = dynamic_cast<EventMessage*>(event))
                m_events_message.emplace_back(std::shared_ptr<EventMessage>(ptr));
            if (auto ptr = dynamic_cast<EventQuery*>(event))
                m_events_query.emplace_back(std::shared_ptr<EventQuery>(ptr));
            if (auto ptr = dynamic_cast<EventError*>(event))
                m_eventmanager->_bindEventError(std::shared_ptr<EventError>(ptr));

            return _impl;
        }

    public:
        void _processMessage(const std::shared_ptr<IEventObject<Message>>& object);

        void _processQuery(const std::shared_ptr<IEventObject<Query>>& object);

    private:
        std::shared_ptr<EventManager> m_eventmanager;

        std::vector<std::shared_ptr<EventMessage>> m_events_message;
        std::vector<std::shared_ptr<EventQuery>> m_events_query;

    private:
        std::shared_ptr<EventHandler> _impl;

    };

} // namespace Bot

#endif // __EVENT_HANDLER_HPP
