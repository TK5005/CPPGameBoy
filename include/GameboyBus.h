#ifndef GAMEBOY_BUS
#define GAMEBOY_BUS

#include <vector>
#include <map>
#include <string>
#include <memory>

class GameboyCPU;
class GameboyMMU;

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

class GameboyBus
{
    public:
        GameboyBus();
        void subscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber);
        void unsubscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber);
        void publishEvent(const std::string& eventType, const Event& event);
        void setCPU(GameboyCPU* cpu);
        void setMMU(GameboyMMU* mmu);
    private:
        std::map<std::string, std::vector<IEventSubscriber*>> subscribers;
        GameboyCPU* cpu;
        GameboyMMU* mmu;
};

#endif