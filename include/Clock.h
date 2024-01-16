#ifndef CLOCK
#define CLOCK

#include <iostream>
#include <chrono>
#include <thread>

class Clock
{
    public:
        Clock();
        bool update();
    private:
        void restartClock();
        std::chrono::high_resolution_clock::time_point start;
};

#endif // CLOCK