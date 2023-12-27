#include <iostream>

#include "GameboyCPU.h"

GameboyCPU::GameboyCPU()
{

}

void GameboyCPU::sayHi()
{
    std::cout << "Hello from CPU" << std::endl;
}

void GameboyCPU::attach(ICPUObserver* observer)
{
    observers.push_back(observer);
}

void GameboyCPU::detach(ICPUObserver* observer)
{
    observers.remove(observer);
}

void GameboyCPU::notify()
{
    std::list<ICPUObserver*>::iterator iterator = observers.begin();
    while(iterator != observers.end())
    {
        (*iterator)->update();
        ++iterator;
    }
}

void GameboyCPU::setState(std::unique_ptr<IGameboyCPUState> state)
{
    currentState = std::move(state);
}

void GameboyCPU::handleInput()
{
    currentState->handleInput(*this);
}

void GameboyCPU::update()
{
    currentState->update(*this);
}

/*
void CPU::someMethodThatChangesState() {
    // Some condition that triggers a state change
    if (condition to halt) {
        setState(std::make_unique<HaltedState>());
    } else {
        setState(std::make_unique<NormalState>());
    }
}
*/