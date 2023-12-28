#include "Opcodes.h"

void OpcodeInvoker::setOpcode(std::unique_ptr<IOpcode> op)
{
    opcode = std::move(op);
}

void OpcodeInvoker::execute()
{
    if(opcode)
    {
        opcode->execute();
    }
}

void NewOpcode::execute()
{
    std::cout << "Executing Command A" << std::endl;
}