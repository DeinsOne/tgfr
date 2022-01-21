# Tgfr

## Overview ##

Tgfr is a c++ library for building high loaded telegram bots.

It provides set of tools to simplify building of business logic and hide low level operations.

## Project Goals ##

The goal of this project is to build c++ interface for creating telegram bots serving of hundreds users the same time with simple separated project structure.

## Usage ##

The following code snippets show how you might implement a simple bot.

File main.cpp:

Include the headers

```cpp
    #include <tgfr/tgfr.hpp>
    #include "example/user/definitions/EventStart.hpp"
```

Initialize helpers. Make manager with maximum 10 same time processing events and 1 minute max lifetime

```cpp
    auto eventmanager = EventManager::make_manager(10, std::chrono::minutes(1));
    auto eventhandler = EventHandler::make_handler(eventmanager);
```

Add events to be handled

```cpp
    eventhandler->addEvent<Events::EventStart>();
```

Start bot with BotSync or BotAsync executor

```cpp
    auto bot = Bot::make_bot(eventmanager, eventhandler, "!!! TOKEN !!!");
    bot->start<BotSync>();
```

File EventStart.hpp:

Include headers

```cpp
    #include <tgfr/handler/Event.hpp>
```

Define class EventStart

```cpp
    class EventStart : public EventMessage {
        EVENT_MESSAGE_CLASS(EventStart)

    public:
        virtual bool Check(const std::shared_ptr<IEventObject<Message>>& eventobject) override;

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override;
    };
```

Define EventStart class functions

```cpp
    bool EventStart::Check(const std::shared_ptr<IEventObject<Message>>& eventobject) {
        return eventobject->GetData() == "/start";
    }

    void Handle(const std::shared_ptr<TgBot::Bot>& bot) {
        bot->getApi().sendMessage(m_eventobject->GetImpl()->from->id, "Hi! Nice to meat you");
    }
```

## Building ##

Tgfr uses cmake build system. Cmake project is located in root directory of the project

```
    mkdir build
    cd build
    cmake -DCMAKE_BUILD_TYPE=Release ..
    make
```

### Build options
```
    -DBUILD_SHARED_LIBS     # Build shared library instead dynamic
    -DBUILD_SAMPLES         # Build samples
```

## Dependencies ##

Tgfr is built over [tgbot-cpp](https://github.com/reo7sp/tgbot-cpp) library. Deps will be automatically installed with inbuilt script.

```
    ./utilities/install-deps.sh
```

