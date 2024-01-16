#include "Clock.h"

Clock::Clock() {
    this->restartClock();
}

void Clock::restartClock() {
    start = std::chrono::high_resolution_clock::now();
}

bool Clock::update() {
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::nano> elapsed = now - start; // Modify this line
    if(elapsed.count() >= 238) // 238 Modify this line
    {
        restartClock();
        return true;
    }
   
}