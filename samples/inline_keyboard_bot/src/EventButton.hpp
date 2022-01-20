#ifndef __EVENT_BUTTON_HPP
#define __EVENT_BUTTON_HPP

#include <tgfr/handler/Event.hpp>
#include <tgfr/utils.hpp>

using namespace tgfr;

namespace Events {

    class EventButton : public EventQuery {
        EVENT_QUERY_CLASS(EventButton)

    public:
        virtual bool Check(const std::shared_ptr<IEventObject<Query>>& eventobject) override {
            return eventobject->GetData() == "_button_callback";
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            // Delete message where the button was pressed
            bot->getApi().deleteMessage(m_eventobject->GetImpl()->from->id, m_eventobject->GetImpl()->message->messageId);

            // Format message text
            std::string text = "Tada. You " + formatStroke("pressed", "html") + " the button!";

            // Send new massage with text
            bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, text, false, 0, NULL, "HTML");
        }

    };

} // namespace Events


#endif // __EVENT_BUTTON_HPP
