#ifndef __BOT_HPP
#define __BOT_HPP

#include <string>

#include <tgfr/Logger.h>
#include <tgfr/BotThreading.hpp>
#include <tgfr/manager/EventManager.hpp>
#include <tgfr/handler/EventHandler.hpp>

namespace tgfr {

    /**
     * @brief Bot instance
     * @details Must be instantiated with make_shared function
     */
    class Bot {
    public:
        Bot(const std::string& token,
            const std::shared_ptr<EventManager>& eventmanage,
            const std::shared_ptr<EventHandler>& eventhandler
        );

        /**
         * @brief Function to create bot
         * 
         * @param eventmanage EventManager instance
         * @param eventhandler EventHandler instace
         * @param token Telegram bot token
         * @return std::shared_ptr<Bot> Pointer to created bot
         */
        static std::shared_ptr<Bot> make_bot(
            const std::shared_ptr<EventManager>& eventmanage,
            const std::shared_ptr<EventHandler>& eventhandler,
            const std::string& token
        ) {
            return std::make_shared<Bot>(token, eventmanage, eventhandler);
        }

        /**
         * @brief Start bot with specific executor
         * 
         * @tparam ThreadingType accepts childs of __IBotThreadingType(BotAsync or BotSync)
         */
        template<typename ThreadingType>
        void start() {
            if (m_executor) {
                m_executor->_stop();
                m_executor.reset();
            }
            m_executor = std::make_shared<ThreadingType>();
            m_executor->_start(m_bot);
        }

        /**
         * @brief Stops bot execution
         */
        void stop() { m_executor->_stop(); }

    protected:
        std::shared_ptr<EventManager> m_eventmanage;
        std::shared_ptr<EventHandler> m_eventhandler;

        std::shared_ptr<TgBot::Bot> m_bot;

    private:
        std::shared_ptr<__IBotThreadingType> m_executor;
    };


} // namespace Bot

#endif // __BOT_HPP
