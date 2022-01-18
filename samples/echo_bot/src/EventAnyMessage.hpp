#ifndef __EVENT_ANY_MESSAGE_HPP
#define __EVENT_ANY_MESSAGE_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

using namespace tgfr;

namespace Events {

    class EventAnyMessage : public EventMessage {
    public:
        EventAnyMessage() = default;
        EventAnyMessage(const std::shared_ptr<IEventObject<Message>>& eventobject) : EventMessage(eventobject) {}  

        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return true;
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, m_eventobject->GetData());
        }

        virtual std::shared_ptr<IEvent<IEventObject<Message>>> make_copy(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return std::make_shared<EventAnyMessage>(eventobject);
        }

    };

} // namespace Events


#endif // __EVENT_ANY_MESSAGE_HPP
