
#include <tgfr/Logger.h>
#include <tgfr/Bot.hpp>

#include "EventStart.hpp"
#include "EventAnyMessage.hpp"

using namespace tgfr;

int main(int argc, char** argv) {
    Logger::Init();

    // Create event manager executing maximum 10 asynchronous events with max 1 minute lifetime
    auto eventmanager = EventManager::make_manager(10, std::chrono::minutes(1));

    // Create event handler with previously created manager
    auto eventhandler = EventHandler::make_handler(eventmanager);

    // Initiate handler with events
    eventhandler->addEvent<Events::EventAnyMessage>();
    eventhandler->addEvent<Events::EventStart>();

    // Or
    // auto eventhandler = EventHandler::make_handler(eventmanager)
    //     ->addEvent<Events::EventAnyMessage>()
    //     ->addEvent<Events::EventStart>();


    // Create bot
    auto bot = Bot::make_bot(eventmanager, eventhandler, "5022108389:AAEQVU1BvRL1JoeRQRaZgd9FM0NxS7_V6lU");

    // Start bot with BotSync executor. Means bot will be executed in the same thread as the program
    bot->start<BotSync>();

    return 0;
}

