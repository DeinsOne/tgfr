#ifndef __EVENT_QUEUE_HPP
#define __EVENT_QUEUE_HPP

#include <tgfr/handler/EventExecutable.h>
#include <tgfr/manager/EventWorker.hpp>
#include <queue>


namespace tgfr {

    /**
     * @brief EventQueue is temporary storage for events
     */
    class EventQueue {
    public:
        /**
         * @brief Get first event from queue and erase it
         * 
         * @return std::shared_ptr<IEventExecutable> Event pointer
         */
        std::shared_ptr<IEventExecutable> popEvent() {
            if (!size()) return nullptr;
            std::lock_guard<std::mutex> _lock(m_events_lock);
            auto event = m_events.front();
            m_events.pop();
            return event;
        }

        /**
         * @brief Add event tu queue
         * 
         * @param event Any event inherited from IEventExecutable
         */
        void addEvent(const std::shared_ptr<IEventExecutable>& event) {
            std::lock_guard<std::mutex> _lock(m_events_lock);
            m_events.push(event);
        }

        /**
         * @brief Get size of queue
         * 
         * @return std::size_t Queue size
         */
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
