#ifndef __EVENT_ERROR_HPP
#define __EVENT_ERROR_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

// using namespace tgfr;

namespace Events {

    class CustomEventError : public tgfr::EventError {
    public:
        CustomEventError() = default;
        CustomEventError(const std::shared_ptr<tgfr::IEventObject<std::string>>& exception, const std::shared_ptr<tgfr::IEventExecutable>& badevent) : tgfr::EventError(exception, badevent) {}

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            ERROR("EventWorker custom -> usr[{}] {}", m_badevent->GetOwner()->id, m_eventobject->GetData());
        }

        virtual std::shared_ptr<IEvent<IEventObject<std::string>>> make_copy(const std::shared_ptr<IEventObject<std::string>>& exception, const std::shared_ptr<tgfr::IEventExecutable> badevent) override {
            return std::make_shared<CustomEventError>(exception, badevent);
        }

    };

} // namespace Events


#endif // __EVENT_ERROR_HPP
