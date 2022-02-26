
#include <tgfr/tgfr.hpp>

#include "Counter.hpp"
#include "EventStart.hpp"
#include "EventAnyMessage.hpp"

using namespace tgfr;

int main(int argc, char** argv) {
    tgfr::Init();

    auto counter = std::make_shared<Counter>();

    auto eventmanager = EventManager::make_manager(10, std::chrono::minutes(1));
    auto eventhandler = EventHandler::make_handler(eventmanager);

    eventhandler->addEvent<Events::EventAnyMessage>(counter);
    eventhandler->addEvent<Events::EventStart>();

    auto bot = Bot::make_bot(eventmanager, eventhandler, "!!! Token !!!");

    bot->start<BotSync>();

    return 0;
}

