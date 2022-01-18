#include <tgfr/BotThreading.hpp>
#include <tgfr/Logger.h>

#include <tgbot/tgbot.h>

namespace tgfr {

    void BotAsync::_stop() {
        m_alive = false;
        std::lock_guard<std::mutex> _lock(m_lock);
        INFO("BotAsync -> stop bot. exit longpool");
    }

    void BotAsync::_start(const std::shared_ptr<TgBot::Bot>& bot) {
        m_worker = std::thread([&](const std::shared_ptr<TgBot::Bot>& _bot) {
            try {
                INFO("BotAsync -> start bot in asynchronous threading");
                INFO("BotAsync -> usr[{}] {}", bot->getApi().getMe()->id, bot->getApi().getMe()->username);
                m_alive = true;

                try {
                    TgBot::TgLongPoll pool(*_bot, 1, 1);
                    while (m_alive) {
                        std::lock_guard<std::mutex> _lock(m_lock);
                        pool.start();
                    }
                }
                catch (const TgBot::TgException& e) {
                    ERROR("BotAsync -> {}", e.what());
                }
            }
            catch (const TgBot::TgException& e) {
                CRITICAL("BotAsync -> {}", e.what());
            }

        }, bot);
        m_worker.detach();
    }

} // namespace Bot
