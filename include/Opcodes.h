#ifndef OPCODES
#define OPCODES

#include <iostream>
#include "GameboyCPU.h"
#include <memory>

class IOpcode
{
    public:
        virtual ~IOpcode() = default;
        virtual void execute() = 0;
};

class OpcodeInvoker
{
    std::unique_ptr<IOpcode> opcode;

    public:
        void setOpcode(std::unique_ptr<IOpcode> opcode);
        void execute();
};

class NewOpcode : public IOpcode
{
    GameboyCPU& cpu;

    public:
        NewOpcode(GameboyCPU& cpu) : cpu(cpu){};
        void execute() override;
};

#endif