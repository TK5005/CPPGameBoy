#include "../include/GameboyCPU.h"
#include "../include/GameboyMMU.h"
#include "../include/Opcodes.h"

int main()
{
    GameboyBus bus;
    GameboyMMU mmu(bus);
    GameboyCPU cpu(bus);

/*  TestEvent tEvent;

    bus.subscribeToEvent(TestEvent::TEST_1, &cpu);
    bus.publishEvent(TestEvent::TEST_1, tEvent);
    bus.unsubscribeToEvent(TestEvent::TEST_1, &cpu);
    bus.publishEvent(TestEvent::TEST_1, tEvent);
*/

    return 0;
}