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

void GameboyBus::registerHandler(const std::string& requestType, IRequestHandler* handler)
{
    handlers[requestType] = handler;
}

void  GameboyBus::unregisterHandler(const std::string& requestType) {
    handlers.erase(requestType);
}

std::unique_ptr<Response> GameboyBus::processRequest(const std::string& requestType, const Request& request)
{
    if (handlers.find(requestType) != handlers.end()) {
        std::unique_ptr<Response> response = std::unique_ptr<Response>(handlers[requestType]->handleRequest(request));
        if(response)
        {
            return response;
        }
    }
    return nullptr;
}