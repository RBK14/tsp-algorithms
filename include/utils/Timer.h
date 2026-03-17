#pragma once
#include <chrono>

class Timer {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

    public:
        void start();

        void stop();

        long long getElapsedMicroseconds() const;

        double getElapsedMilliseconds() const;
};