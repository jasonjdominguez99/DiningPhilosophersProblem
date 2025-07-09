#pragma once

#include <latch>
#include <mutex>
#include <random>

struct PhilosopherContext
{
    std::mutex&                      outputMutex;
    std::mutex&                      randomMutex;
    std::mt19937&                    randomGenerator;
    std::uniform_int_distribution<>& thinkingTimeDist;
    std::uniform_int_distribution<>& eatingTimeDist;
    std::latch&                      startLatch;
};
