#ifndef __EVENT_WORKER_HPP
#define __EVENT_WORKER_HPP

#include <memory>
#include <chrono>
#include <thread>

#include <tgfr/handler/EventExecutable.h>
#include <tgfr/Logger.h>

namespace tgfr {

    class EventError;

    /**
     * @brief EventWorker handles event
    */
    class EventWorker {
    public:
        /**
         * @brief Construct a new Event Worker object
         * 
         * @param event Any event inherited from IEventExecutable
         * @param bot Bot instance
         * @param eventerror Event error in case of any exception
         * @param callback Callback to be called when event is done
         */
        EventWorker(const std::shared_ptr<IEventExecutable>& event, const std::shared_ptr<TgBot::Bot>& bot, const std::shared_ptr<EventError> eventerror, std::function<void()> callback);

        /**
         * @brief Check if event is done
         * 
         * @param max_lifetime Maximum event lifetime
         * @return true or false 
         */
        template<typename _Clock, typename _Dur>
        bool IsDone(const std::chrono::duration<_Clock, _Dur>& max_lifetime) {
            return std::chrono::high_resolution_clock::now() - m_initiated > max_lifetime || m_ready;
        }

    private:
        std::thread m_thread;
        std::chrono::high_resolution_clock::time_point m_initiated;
        bool m_ready;
        std::shared_ptr<IEventExecutable> m_event;
    };

} // namespace Bot


#endif // __EVENT_WORKER_HPP
