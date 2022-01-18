#ifndef __EVENT_START_HPP
#define __EVENT_START_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils-bot.hpp>

using namespace tgfr;

namespace Events {

    class EventStart : public EventMessage {
    public:
        EventStart() = default;
        EventStart(const std::shared_ptr<IEventObject<Message>>& eventobject) : EventMessage(eventobject) {}  

        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return eventobject->GetData() == "/start";
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, "Hi! Nice to meat you");
        }

        virtual std::shared_ptr<IEvent<IEventObject<Message>>> make_copy(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return std::make_shared<EventStart>(eventobject);
        }

    };

} // namespace Events


#endif // __EVENT_START_HPP
