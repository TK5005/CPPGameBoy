#ifndef GAMEBOY_CPU_STATES
#define GAMEBOY_CPU_STATES

class GameboyCPU;

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