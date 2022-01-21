#ifndef __BOT_THREADING_HPP
#define __BOT_THREADING_HPP

#include <thread>
#include <mutex>

#include <tgbot/Bot.h>


namespace tgfr {

    /**
     * @brief Interface for bot executer classes
     */
    class __IBotThreadingType {
    public:
        /**
         * @brief Function to stop bot exectuing
         */
        virtual void _stop() = 0;

        /**
         * @brief Function to start current bot executer
         * 
         * @param bot Bot to be executed
         */
        virtual void _start(const std::shared_ptr<TgBot::Bot>& bot) = 0;
    };

    /**
     * @brief BotAsync runs bot in separate thread from main program
     * @note Provides nonblocking execution flow
    */
    class BotAsync : public __IBotThreadingType {
    public:
        BotAsync() = default;

        virtual void _stop() override;

        virtual void _start(const std::shared_ptr<TgBot::Bot>& bot) override;

    private:
        bool m_alive;
        std::mutex m_lock;
        std::thread m_worker;
    };

    /**
     * @brief BotSync executes bot in the executor thread
     * @note Blocks executor thread
    */
    class BotSync : public __IBotThreadingType {
    public:
        BotSync() = default;

        virtual void _stop() override;

        virtual void _start(const std::shared_ptr<TgBot::Bot>& bot) override;

    private:
        bool m_alive;
        std::mutex m_lock;
    };



} // namespace Bot


#endif // __BOT_THREADING_HPP
