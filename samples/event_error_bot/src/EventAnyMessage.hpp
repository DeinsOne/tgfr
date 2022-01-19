#ifndef __EVENT_ANY_MESSAGE_HPP
#define __EVENT_ANY_MESSAGE_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

using namespace tgfr;

namespace Events {

    class EventAnyMessage : public EventMessage {
        EVENT_MESSAGE_CLASS(EventAnyMessage)

    public:
        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return true;
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            throw std::runtime_error("EventAnyMessage: Some error");
            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, m_eventobject->GetData());
        }

    };

} // namespace Events


#endif // __EVENT_ANY_MESSAGE_HPP
