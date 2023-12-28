#ifndef GAMEBOY_CPU
#define GAMEBOY_CPU

#include <list>
#include <cstdint>
#include <memory>

#include "GameboyBus.h"

class IGameboyCPUState;

class GameboyCPU : public IEventSubscriber, public IRequestHandler
{
    public:
        // Constructor
        GameboyCPU(GameboyBus& bus);
        void onEvent(const Event& event);
        Response* handleRequest(const Request& request);
    private:
        GameboyBus& bus;
        std::unique_ptr<IGameboyCPUState> currentState;

        // CPU Registers
        union {
            struct {
                uint8_t F; // Flag register
                uint8_t A; // Accumulator
            };
            uint16_t AF;
        };

        union {
            struct {
                uint8_t C;
                uint8_t B;
            };
            uint16_t BC;
        };

        union {
            struct {
                uint8_t E;
                uint8_t D;
            };
            uint16_t DE;
        };

        union {
            struct {
                uint8_t L;
                uint8_t H;
            };
            uint16_t HL;
        };

        uint16_t SP; // Stack Pointer
        uint16_t PC; // Program Counter

        // State logic
        void setState(std::unique_ptr<IGameboyCPUState> state);
        void handleInput();
        void update();  
};

class IGameboyCPUState
{
    public:
        virtual ~IGameboyCPUState() = default;
        virtual void handleInput(GameboyCPU& cpu) = 0;
        virtual void update(GameboyCPU& cpu) = 0;
};

class NormalState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

class HaltedState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

class StoppedState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

class InterruptState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

class DMATransferState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

class BootState : public IGameboyCPUState
{
    void handleInput(GameboyCPU& cpu) override;
    void update(GameboyCPU& cpu) override;
};

#endif