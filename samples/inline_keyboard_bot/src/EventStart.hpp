#ifndef __EVENT_START_HPP
#define __EVENT_START_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

using namespace tgfr;

namespace Events {

    class EventStart : public EventMessage {
        EVENT_MESSAGE_CLASS(EventStart)

    public:
        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
            return eventobject->GetData() == "/start";
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, "Hi! Nice to meat you");
        }

    };

} // namespace Events


#endif // __EVENT_START_HPP
