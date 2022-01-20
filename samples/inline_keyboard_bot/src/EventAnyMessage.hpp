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
            auto kb = createInlineKeyboard({
                { { "Press me!", "_button_callback" } }
            });

            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, formatItalic(m_eventobject->GetData(), "html"), true, 0, kb, "HTML");
        }

    };

} // namespace Events


#endif // __EVENT_ANY_MESSAGE_HPP
