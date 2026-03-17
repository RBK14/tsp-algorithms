#include "utils/Timer.h"

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    endTime = std::chrono::high_resolution_clock::now();
}

long long Timer::getElapsedMicroseconds() const {
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    return elapsed.count();
}

double Timer::getElapsedMilliseconds() const {
    return getElapsedMicroseconds() / 1000.0;
}