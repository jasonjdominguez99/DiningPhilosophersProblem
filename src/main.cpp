#include <latch>
#include <print>
#include <stop_token>
#include <thread>

#include "Fork.h"
#include "LeftHandedPhilosopher.h"
#include "OrderedPhilosopher.h"
#include "PhilosophersFactory.h"
#include "RightHandedPhilosopher.h"
#include "SimulationConfig.h"

int main()
{
    const SimulationConfig config; // default configuration
    const auto& [NumPhilosophers, strategy, TotalRunTime, MinThinkingTime, MaxThinkingTime, MinEatingTime, MaxEatingTime] = config;

    std::println("Dining Philosophers Problem");
    std::println("Preparing philosophers...");

    std::latch startLatch(NumPhilosophers + 1); // number of philosophers + main thread

    std::mutex outputMutex;

    std::mutex                      randomMutex;
    std::random_device              rd;
    std::mt19937                    randomGenerator(rd());
    std::uniform_int_distribution<> thinkingTimeDist(MinThinkingTime, MaxThinkingTime);
    std::uniform_int_distribution<> eatingTimeDist(MinEatingTime, MaxEatingTime);

    const PhilosopherContext context { outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist, startLatch };

    std::vector<std::unique_ptr<Fork>> forks;
    forks.reserve(NumPhilosophers);
    for (size_t i = 0; i < NumPhilosophers; ++i)
    {
        forks.emplace_back(std::make_unique<Fork>(i + 1)); // Fork IDs start from 1
    }

    auto philosophers = PhilosophersFactory::create(forks, strategy);

    std::vector<std::jthread> philosopherThreads;
    philosopherThreads.reserve(NumPhilosophers);
    for (size_t i = 0; i < NumPhilosophers; ++i)
    {
        philosopherThreads.emplace_back([&](std::stop_token stopToken, size_t id)
                                        { philosophers[id]->start(context, stopToken); },
                                        i);
    }

    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::println("Philosophers may start eating!");
    }
    startLatch.arrive_and_wait(); // Wait for all philosophers to be ready

    std::this_thread::sleep_for(std::chrono::milliseconds(TotalRunTime));
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::println("Stopping philosophers...");
    }

    return 0;
}
