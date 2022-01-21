# Tgfr

## Overview ##

Tgfr is a c++ library for building high loaded telegram bots.

It provides set of tools to simplify building of business logic and hide low level operations.

## Project Goals ##

The goal of this project is to build c++ interface for creating telegram bots serving of hundreds users the same time with simple separated project structure.

## Usage ##

The following code snippets show how you might implement a simple bot.

main.cpp

```cpp
#include <tgfr/tgfr.hpp>
#include "EventStart.hpp"

int main(int argc, char** argv) {
    tgfr::Init();

    // Make event manager with maximum 10 same time processing events and 1 minute max lifetime
    auto eventmanager = tgfr::EventManager::make_manager(10, std::chrono::minutes(1));

    // Make event handler
    auto eventhandler = tgfr::EventHandler::make_handler(eventmanager);

    // Add events to be handled
    eventhandler->addEvent<Events::EventStart>();

    // Make bot with specific token
    auto bot = tgfr::Bot::make_bot(eventmanager, eventhandler, "!!! TOKEN !!!");

    // Start bot with BotSync executor or BotAsync
    bot->start<tgfr::BotSync>();

    return 0;
}
```

EventStart.hpp

```cpp
#include <tgfr/handler/Event.hpp>

// Class inherited from EventMessage. You should override Check and Handle methods only
class EventStart : public EventMessage {
    EVENT_MESSAGE_CLASS(EventStart)

public:
    // Method to check the event can be handled. Check if message text is '/start'
    virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override {
        return eventobject->GetData() == "/start";
    }

    // Handle event. Send some message in response
    virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
        bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, "Hi! Nice to meat you");
    }
};
```

See more samples on [samples](./samples)

## Building ##

Tgfr uses cmake build system. Cmake project is located in root directory of the project

```bash
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
```

### Build options
```
-DTGFR_BUILD_SHARED_LIBS     # Build shared library instead dynamic
-DTGFR_BUILD_SAMPLES         # Build samples
```

### Use in projects ###

To use tgfr as library use the instruction:

```bash
cd <project-path>
git submodule add https://github.com/DeinsOne/tgfr.git third-party/tgfr
```

Before the target add the module subdirectory in your CMakeLists.txt

```cmake
add_subdirectory(third-party/tgfr)
add_executable(your-executable ...)
target_link_libraries(your-executable tgfr)
```

## Dependencies ##

Tgfr requires a compiler with C++11 support. The library is built over [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) library. Deps will be automatically installed with inbuilt script.

```bash
./utilities/install-deps.sh
```

## Documentation ##

Doxygen documentation can be built by running 'doxygen' from the project root directory. Generated documentation will be placed in 'doc/html'.
