#include <tgfr/manager/EventManager.hpp>
#include <tgfr/handler/Event.hpp>

namespace tgfr {

    EventManager::EventManager(const std::size_t& max_async_events, const std::chrono::seconds& max_timeout)
     : m_max_async_events(max_async_events), m_max_timeout(max_timeout), m_event_error(new EventError) {
    }

    EventWorker::EventWorker(const std::shared_ptr<IEventExecutable>& event, const std::shared_ptr<TgBot::Bot>& bot, const std::shared_ptr<EventError> eventerror, std::function<void()> callback) : m_event(event) {
        m_ready = false;
        m_thread = std::thread([&](const std::shared_ptr<TgBot::Bot>& _bot, const std::shared_ptr<EventError> _eventerror, std::function<void()> _callback) {
            m_initiated = std::chrono::high_resolution_clock::now();
            try {
                m_event->Handle(_bot);
            }
            catch (const std::exception& e) {
                auto errorobject = EventObjectError::make_object(e.what());

                auto err = _eventerror->make_copy(errorobject, m_event);
                err->Handle(_bot);
            }

            m_ready = true;
            _callback();
        }, bot, eventerror, callback);
        m_thread.detach();
    }

} // namespace tgfr
