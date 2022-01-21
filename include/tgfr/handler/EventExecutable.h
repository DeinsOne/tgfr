#ifndef __EVENT_EXECUTABLE_HPP
#define __EVENT_EXECUTABLE_HPP

#include <memory>
#include <tgbot/Bot.h>

#include <tgbot/types/User.h>
#include <tgbot/types/Chat.h>

namespace tgfr {

    /**
     * @brief IEventExecutable is an interface for IEvent
     */
    class IEventExecutable {
    public:
        /**
         * @brief Handles current event
         * @param bot Bot instacne accepting event 
         */
        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) = 0;

        /**
         * @brief Get the Owner object
         * @return TgBot::User::Ptr Owner
         */
        virtual TgBot::User::Ptr GetOwner() = 0;

        /**
         * @brief Get the Chat object
         * @return TgBot::Chat::Ptr Chat
         */
        virtual TgBot::Chat::Ptr GetChat() = 0;

    };

} // namespace Bot

#endif // __EVENT_EXECUTABLE_HPP
