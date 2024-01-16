#include "Clock.h"

#include <SFML/System/Clock.hpp>
#include <iostream>

#include <ctime> // Add this include statement

int main() {
    std::cout << "Running clock test" << std::endl;
    
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
    Clock clock;
    while(true)
    {
        if(clock.update())
        {
            std::chrono::duration<double, std::nano> elapsed = std::chrono::high_resolution_clock::now() - start;
            std::cout << "Elapsed time: " << elapsed.count() << std::endl;

            
            return 0;
        }
    }
    return 0;
}