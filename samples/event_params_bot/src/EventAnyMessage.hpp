#ifndef __EVENT_ANY_MESSAGE_HPP
#define __EVENT_ANY_MESSAGE_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

#include "Counter.hpp"

using namespace tgfr;

namespace Events {

    class EventAnyMessage : public EventMessage {
        EVENT_MESSAGE_CLASS(EventAnyMessage)

    public:
        EventAnyMessage(const std::shared_ptr<Counter>& counter) {
            EventAnyMessage::m_counter = counter;
        }

        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return true;
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override;

    private:
        static std::shared_ptr<Counter> m_counter;

    };


    std::shared_ptr<Counter> EventAnyMessage::m_counter;

    void EventAnyMessage::Handle(const std::shared_ptr<TgBot::Bot>& bot) {
        EventAnyMessage::m_counter->add();
        bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, m_eventobject->GetData() + " id: " + std::to_string(m_counter->get()));
    }


} // namespace Events


#endif // __EVENT_ANY_MESSAGE_HPP
