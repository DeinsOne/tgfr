#ifndef __EVENT_QUEUE_HPP
#define __EVENT_QUEUE_HPP

#include <tgfr/handler/EventExecutable.h>
#include <tgfr/manager/EventWorker.hpp>
#include <queue>


namespace tgfr {

    class EventQueue {
    public:
        std::shared_ptr<IEventExecutable> popEvent() {
            if (!size()) return nullptr;
            std::lock_guard<std::mutex> _lock(m_events_lock);
            auto event = m_events.front();
            m_events.pop();
            return event;
        }

        void addEvent(const std::shared_ptr<IEventExecutable>& event) {
            std::lock_guard<std::mutex> _lock(m_events_lock);
            m_events.push(event);
        }

        std::size_t size() {
            std::lock_guard<std::mutex> _lock(m_events_lock);
            return m_events.size();
        }

    private:
        std::mutex m_events_lock;
        std::queue<std::shared_ptr<IEventExecutable>> m_events;
    };

} // namespace tgfr


#endif // __EVENT_QUEUE_HPP
