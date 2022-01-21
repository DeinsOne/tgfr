#ifndef __EVENT_HPP
#define __EVENT_HPP

#include <memory>
#include <tgfr/handler/EventObject.hpp>
#include <tgfr/handler/EventExecutable.h>

#include <tgbot/Bot.h>

namespace tgfr {

    /**
     * @brief Interface for making events
     * @tparam TEventObject Type of object event will handle
     */
    template<typename TEventObject>
    class IEvent : public IEventExecutable {
    public:
        IEvent() = default;
        IEvent(const std::shared_ptr<TEventObject>& eventobject);

        /**
         * @brief Get the Event Object object
         * @return std::shared_ptr<TEventObject> Event object
         */
        virtual std::shared_ptr<TEventObject> GetEventObject() = 0;

        /**
         * @brief Function to instantiate class
         * @param eventobject Event object
         * @return std::shared_ptr<IEvent<TEventObject>> New event
         */
        virtual std::shared_ptr<IEvent<TEventObject>> make_copy(const std::shared_ptr<TEventObject>& eventobject) = 0;

    public:
        /**
         * @brief Check whater given event object is compatible with event
         * @param eventobject Event object to be checked
         * @return true or false 
         */
        virtual bool Check(const std::shared_ptr<TEventObject>& eventobject) = 0;
    };


    /**
     * @brief Event of Message object
     */
    class EventMessage : public IEvent<IEventObject<Message>> {
    public:
        EventMessage() = default;
        EventMessage(const std::shared_ptr<IEventObject<Message>>& eventobject) : m_eventobject(eventobject) {
        }

        virtual std::shared_ptr<IEventObject<Message>> GetEventObject() override { return m_eventobject; }

        virtual TgBot::User::Ptr GetOwner() override {
            return m_eventobject->GetOwner();
        }

        virtual TgBot::Chat::Ptr GetChat() override {
            return m_eventobject->GetChat();
        }

    protected:
        std::shared_ptr<IEventObject<Message>> m_eventobject;
    };


    /**
     * @brief Event of Query object
     */
    class EventQuery : public IEvent<IEventObject<Query>> {
    public:
        EventQuery() = default;
        EventQuery(const std::shared_ptr<IEventObject<Query>>& eventobject) : m_eventobject(eventobject) {
        }

        virtual std::shared_ptr<IEventObject<Query>> GetEventObject() override { return m_eventobject; }

        virtual TgBot::User::Ptr GetOwner() override {
            return m_eventobject->GetOwner();
        }

        virtual TgBot::Chat::Ptr GetChat() override {
            return m_eventobject->GetChat();
        }

    protected:
        std::shared_ptr<IEventObject<Query>> m_eventobject;
    };


    /**
     * @brief Event of Error object
     */
    class EventError : public IEvent<IEventObject<std::string>> {
    public:

        EventError() = default;
        EventError(const std::shared_ptr<IEventObject<std::string>>& exception) : m_eventobject(exception) {}
        EventError(const std::shared_ptr<IEventObject<std::string>>& exception, const std::shared_ptr<IEventExecutable>& badevent) : m_eventobject(exception), m_badevent(badevent) {}


        virtual std::shared_ptr<IEventObject<std::string>> GetEventObject() override { return m_eventobject; }
        virtual TgBot::User::Ptr GetOwner() override { return m_badevent->GetOwner(); }
        virtual TgBot::Chat::Ptr GetChat() override { return m_badevent->GetChat(); }

        virtual std::shared_ptr<IEvent<IEventObject<std::string>>> make_copy(const std::shared_ptr<IEventObject<std::string>>& exception) override {
            return std::make_shared<EventError>(exception);
        }

        virtual std::shared_ptr<IEvent<IEventObject<std::string>>> make_copy(const std::shared_ptr<IEventObject<std::string>>& exception, const std::shared_ptr<IEventExecutable> badevent) {
            return std::make_shared<EventError>(exception, badevent);
        }

        virtual void Handle(const std::shared_ptr<TgBot::Bot>& bot) override {
            // Default handler
            ERROR("EventWorker -> usr[{}] {}", m_badevent->GetOwner()->id, m_eventobject->GetData());
        }

        virtual bool Check(const std::shared_ptr<IEventObject<std::string>>& eventobject) override { return false; }

    protected:
        std::shared_ptr<IEventObject<std::string>> m_eventobject;
        std::shared_ptr<IEventExecutable> m_badevent;
    };

} // namespace Bot


#define EVENT_CLASS_0(CLASS, BASE, OBJECT) \
public: \
    CLASS() = default; \
    CLASS(const std::shared_ptr<OBJECT>& eventobject) : BASE(eventobject) {} \
    virtual std::shared_ptr<IEvent<OBJECT>> make_copy(const std::shared_ptr<OBJECT>& eventobject) override { \
        return std::make_shared<CLASS>(eventobject); \
    }

#define EVENT_MESSAGE_CLASS(CLASS) EVENT_CLASS_0(CLASS, EventMessage, IEventObject<Message>)
#define EVENT_QUERY_CLASS(CLASS) EVENT_CLASS_0(CLASS, EventQuery, IEventObject<Query>)

#define EVENT_ERROR_CLASS(CLASS) \
public: \
    CLASS() = default; \
    CLASS(const std::shared_ptr<IEventObject<std::string>>& exception, const std::shared_ptr<IEventExecutable>& badevent) : EventError(exception, badevent) {} \
    virtual std::shared_ptr<IEvent<IEventObject<std::string>>> make_copy(const std::shared_ptr<IEventObject<std::string>>& exception, const std::shared_ptr<IEventExecutable> badevent) override { \
        return std::make_shared<CLASS>(exception, badevent); \
    }

#endif // __EVENT_HPP
