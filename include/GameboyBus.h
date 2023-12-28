#ifndef GAMEBOY_BUS
#define GAMEBOY_BUS

#include <vector>
#include <map>
#include <string>
#include <memory>

struct Event
{
    virtual ~Event() = default;
};

struct TestEvent : public Event
{
    inline static const std::string TEST_1 = "test1";
};

class IEventSubscriber
{
    public:
        virtual void onEvent(const Event& event) = 0;
};

struct Request
{
    public:
        virtual ~Request() = default;
};

struct TestRequest : public Request
{
    inline static const std::string TEST_1 = "test1";

    public:
        std::string getRequestType() const {return TEST_1;}
};

struct Response
{
    virtual ~Response() = default;
};

struct TestResponse : public Response
{
    int responseData = 0;
};

class IRequestHandler
{
    public:
        virtual Response* handleRequest(const Request& request) = 0;
};

class GameboyBus
{
    public:
        GameboyBus();
        void subscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber);
        void unsubscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber);
        void publishEvent(const std::string& eventType, const Event& event);
        void registerHandler(const std::string& requestType, IRequestHandler* handler);
        void unregisterHandler(const std::string& requestType);
        std::unique_ptr<Response> processRequest(const std::string& requestType, const Request& request);
    private:
        std::map<std::string, std::vector<IEventSubscriber*>> subscribers;
        std::map<std::string, IRequestHandler*> handlers;
};

#endif