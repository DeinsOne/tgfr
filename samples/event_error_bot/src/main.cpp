
#include <tgfr/Logger.h>
#include <tgfr/Bot.hpp>

#include "EventStart.hpp"
#include "EventAnyMessage.hpp"
#include "EventError.hpp"

using namespace tgfr;

int main(int argc, char** argv) {
    Logger::Init();

    auto eventmanager = EventManager::make_manager(10, std::chrono::minutes(1));
    auto eventhandler = EventHandler::make_handler(eventmanager)
        ->addEvent<Events::CustomEventError>()
        ->addEvent<Events::EventAnyMessage>()
        ->addEvent<Events::EventStart>();

    auto bot = Bot::make_bot(eventmanager, eventhandler, "!!! Token !!!");

    bot->start<BotSync>();

    return 0;
}

