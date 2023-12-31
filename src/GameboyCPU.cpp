#include <iostream>

#include "GameboyCPU.h"

GameboyCPU::GameboyCPU(GameboyBus& bus) : bus(bus), AF(0), BC(0), DE(0), HL(0), SP(0), PC(0)
{
    std::cout << "Gameboy CPU Created" << std::endl;
    bus.setCPU(this);
}
    

void GameboyCPU::onEvent(const Event& event)
{
    // TODO: Check through events I'm interested in and act accordingly
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

// STATE CODE

void NormalState::handleInput(GameboyCPU& cpu)
{
}

void NormalState::update(GameboyCPU& cpu)
{
}

void HaltedState::handleInput(GameboyCPU& cpu)
{
}

void HaltedState::update(GameboyCPU& cpu)
{
}

void StoppedState::handleInput(GameboyCPU &cpu)
{
}

void StoppedState::update(GameboyCPU &cpu)
{
}

void InterruptState::handleInput(GameboyCPU &cpu)
{
}

void InterruptState::update(GameboyCPU &cpu)
{
}

void DMATransferState::handleInput(GameboyCPU &cpu)
{
}

void DMATransferState::update(GameboyCPU &cpu)
{
}

void BootState::handleInput(GameboyCPU &cpu)
{
}

void BootState::update(GameboyCPU &cpu)
{
}