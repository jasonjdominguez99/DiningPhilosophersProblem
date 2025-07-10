#pragma once

#include "Strategy.h"

#include <cstddef>

struct SimulationConfig
{
    size_t   numPhilosophers = 5;
    Strategy strategy = Strategy::Hierarchical;
    int      totalRunTime = 10'000; // milliseconds
    int      minThinkingTime = 0;
    int      maxThinkingTime = 1;
    int      minEatingTime = 0;
    int      maxEatingTime = 1;
};
