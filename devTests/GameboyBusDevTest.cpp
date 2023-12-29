#include "../include/GameboyCPU.h"
#include "../include/GameboyMMU.h"
#include "../include/Opcodes.h"

int main()
{
    GameboyBus bus;
    GameboyMMU mmu(bus);
    GameboyCPU cpu(bus);

    TestEvent tEvent;

    bus.subscribeToEvent(TestEvent::TEST_1, &cpu);
    bus.publishEvent(TestEvent::TEST_1, tEvent);
    bus.unsubscribeToEvent(TestEvent::TEST_1, &cpu);
    bus.publishEvent(TestEvent::TEST_1, tEvent);

    bus.registerHandler(TestRequest::TEST_1, &cpu);

    TestRequest tRequest;
    std::unique_ptr<Response> response = bus.processRequest(TestRequest::TEST_1, tRequest);

    TestResponse* testResponse = dynamic_cast<TestResponse*>(response.get());

    if(testResponse)
    {
        int data = testResponse->responseData;
        std::cout << data << std::endl;
    }

    bus.unregisterHandler(TestRequest::TEST_1);
    bus.processRequest(TestRequest::TEST_1, tRequest);

    return 0;
}