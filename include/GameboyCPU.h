#ifndef GAMEBOY_CPU
#define GAMEBOY_CPU

#include <list>
#include <memory>

#include "Observer.h"
#include "GameboyCPUStates.h"

class GameboyCPU : public ICPUSubject
{
    std::list<ICPUObserver*> observers;
    std::unique_ptr<IGameboyCPUState> currentState;

    public:
        GameboyCPU();
        void sayHi();
        void attach(ICPUObserver* observer) override;
        void detach(ICPUObserver* observer) override;
        void setState(std::unique_ptr<IGameboyCPUState> state);
        void handleInput();
        void update();
    private:
        void notify() override;
};

#endif