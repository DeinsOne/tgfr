#include <tgfr/manager/EventWorker.hpp>
#include <tgfr/handler/Event.hpp>

namespace tgfr {

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
