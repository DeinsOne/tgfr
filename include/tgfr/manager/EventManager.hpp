#ifndef __EVENT_MANAGER_HPP
#define __EVENT_MANAGER_HPP

#include <tgfr/manager/EventQueue.hpp>

namespace tgfr {

    class EventError;

    /**
     * @brief EventManager regulates events execution
     * @details EventManager is worker's master who regulates events execution.
     * It operates threads and queue which is initializing externally
     * by EventsHandler class
     * @note Must be instantiated with make_manager function
    */
    class EventManager {
    public:
        EventManager(const std::size_t& max_async_events, const std::chrono::seconds& max_timeout);

        /**
         * @brief Function to create manage
         * 
         * @param max_async_events Maximum number of same time executing events
         * @param max_timeout Maximum event lifetime
         * @return std::shared_ptr<EventManager> Newly created manager
         */
        static std::shared_ptr<EventManager> make_manager(const std::size_t& max_async_events, const std::chrono::seconds& max_timeout) {
            return std::make_shared<EventManager>(max_async_events, max_timeout);
        }

        /**
         * @brief Adds event to queue or executes if possible
         * 
         * @param event Any event inherited from IEventExecutable
         */
        void addEvent(const std::shared_ptr<IEventExecutable>& event) {
            m_events.addEvent(event);
            insertWorkers();
        }

        /**
         * @brief Binds bot to the manager
         * @details Bot takes part in event execution(is passing as argument)
         * 
         * @param bot TgBot::Bot::ptr
         */
        void _bindBot(const std::shared_ptr<TgBot::Bot>& bot) {
            m_bot = bot;
        }

        /**
         * @brief Binds EventError to the manager
         * @details Any error(exception) on event executing will be processed by eventerror
         * 
         * @param eventerror Event inherited from EventError
         */
        void _bindEventError(const std::shared_ptr<EventError> eventerror) {
            m_event_error = eventerror;
        }

    private:
        /**
         * @brief Erases completed workers
         * @details Erases worker if is done or lifetime is due
         */
        void eraseCompletedWorkers() {
            std::lock_guard<std::mutex> _lock(m_workers_lock);
            m_workers.erase(
                std::remove_if(m_workers.begin(), m_workers.end(), [&](std::shared_ptr<EventWorker>& worker) { return worker->IsDone(m_max_timeout); }),
                m_workers.end()
            );
            m_workers.shrink_to_fit();
        }

        /**
         * @brief Executes event from queue
         * @details Executes as much as m_max_async_events events
         */
        void insertWorkers() {
            std::lock_guard<std::mutex> _lock(m_workers_lock);
            if (m_events.size()) {
                while (m_events.size() && m_workers.size() < m_max_async_events) {
                    m_workers.emplace_back(std::make_shared<EventWorker>(m_events.popEvent(), m_bot, m_event_error, [&]() {
                        eraseCompletedWorkers();
                        insertWorkers();
                    }));
                }
            }
        }

    private:
        std::size_t m_max_async_events;
        std::chrono::seconds m_max_timeout;
        std::shared_ptr<TgBot::Bot> m_bot;

        EventQueue m_events;

        std::mutex m_workers_lock;
        std::vector<std::shared_ptr<EventWorker>> m_workers;

        std::shared_ptr<EventError> m_event_error;
    };

} // namespace Bot


#endif // __EVENT_MANAGER_HPP
