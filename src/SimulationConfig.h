#pragma once

#include "Strategy.h"

#include <cstddef>

struct SimulationConfig
{
    size_t   numPhilosophers = 5;
    Strategy strategy = Strategy::Hierarchical;
    int      totalRunTime = 10000; // milliseconds
    int      minThinkingTime = 100;
    int      maxThinkingTime = 300;
    int      minEatingTime = 200;
    int      maxEatingTime = 500;
};
