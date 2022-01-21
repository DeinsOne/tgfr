#ifndef __EVENT_HANDLER_HPP
#define __EVENT_HANDLER_HPP

#include <memory>
#include <tgfr/handler/EventObject.hpp>
#include <tgfr/handler/Event.hpp>
#include <tgfr/manager/EventManager.hpp>

#include <tgbot/Bot.h>

namespace tgfr {

    /**
     * @brief EventHandler instantiates events and fills EventManager
     * @note Must be instantiated with make_handler function
     */
    class EventHandler {
    public:
        EventHandler(const std::shared_ptr<EventManager>& eventmanager) : m_eventmanager(eventmanager) {
        }

        /**
         * @brief Creates handler object
         * @param eventmanager Manager instance. Required for constructor
         * @return std::shared_ptr<EventHandler> 
         */
        static std::shared_ptr<EventHandler> make_handler(const std::shared_ptr<EventManager>& eventmanager) {
            auto handler = std::make_shared<EventHandler>(eventmanager);
            handler->_impl = handler;
            return handler;
        }

    public:
        /**
         * @brief Add event type for handling
         * @tparam TEvent Any event inherited from IEvent's childs
         * @return std::shared_ptr<EventHandler> This handler
         */
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
        /**
         * @brief Checks if message object is compatibles with any registered message event
         * @note Applyes for one or multiple message event
         * @param object Message event object
         */
        void _processMessage(const std::shared_ptr<IEventObject<Message>>& object);

        /**
         * @brief Checks if message object is compatibles with any registered query event
         * @note Applyes for one or multiple quey event
         * @param object Query event object
         */
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
