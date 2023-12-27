#include "GameboyCPU.h"
#include "Opcodes.h"

int main()
{
    GameboyCPU cpu;

    std::unique_ptr<IOpcode> command = std::make_unique<NewOpcode>(cpu);

    OpcodeInvoker invoker;

    invoker.setOpcode(std::move(command));
    invoker.execute();

    return 0;
}