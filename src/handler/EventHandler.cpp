#include <tgfr/handler/EventHandler.hpp>

#include <tgfr/Logger.h>

namespace tgfr {

    void EventHandler::_processMessage(const std::shared_ptr<IEventObject<Message>>& object) {
        TRACE("EventHandler -> message usr[{}]: {} {}", object->GetImpl()->from->id, object->GetAttachmentType(), object->GetData());

        for (auto event : m_events_message) {
            if (event->Check(object)) {
                auto newevent = event->make_copy(object);
                m_eventmanager->addEvent(newevent);
            }
        }
    }

    void EventHandler::_processQuery(const std::shared_ptr<IEventObject<Query>>& object) {
        TRACE("EventHandler -> query usr[{}]: {}", object->GetImpl()->from->id, object->GetData());

        for (auto event : m_events_query) {
            if (event->Check(object)) {
                auto newevent = event->make_copy(object);
                m_eventmanager->addEvent(newevent);
            }
        }
    }

} // namespace Bot
