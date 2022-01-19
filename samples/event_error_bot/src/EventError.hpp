#ifndef __EVENT_ERROR_HPP
#define __EVENT_ERROR_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

// using namespace tgfr;

namespace Events {

    class CustomEventError : public tgfr::EventError {
        EVENT_ERROR_CLASS(CustomEventError)

    public:
        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            ERROR("EventWorker custom -> usr[{}] {}", m_badevent->GetOwner()->id, m_eventobject->GetData());
        }

    };

} // namespace Events


#endif // __EVENT_ERROR_HPP
