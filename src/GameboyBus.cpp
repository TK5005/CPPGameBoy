#include "GameboyBus.h"
#include <iostream>

GameboyBus::GameboyBus()
{
    std::cout << "Gameboy Bus Created" << std::endl;
}

void GameboyBus::subscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber)
{
    subscribers[eventType].push_back(subscriber);
}

void GameboyBus::unsubscribeToEvent(const std::string& eventType, IEventSubscriber* subscriber) {
    auto& subs = subscribers[eventType];
    for (auto it = subs.begin(); it != subs.end(); ) {
        if (*it == subscriber) {
            it = subs.erase(it);
        } else {
            ++it;
        }
    }
}

void GameboyBus::publishEvent(const std::string& eventType, const Event& event)
{
    for (auto* subscriber : subscribers[eventType]) {
        subscriber->onEvent(event);
    }
}

void GameboyBus::setCPU(GameboyCPU* cpu)
{
    std::cout << "Connecting bus to cpu" << std::endl;
    this->cpu = cpu;
}

void GameboyBus::setMMU(GameboyMMU* mmu)
{
    std::cout << "Connecting bus to mmu" << std::endl;
    this->mmu = mmu;
}

