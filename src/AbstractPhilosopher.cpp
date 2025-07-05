#include "AbstractPhilosopher.h"

#include "Fork.h"

#include <iostream>
#include <thread>

AbstractPhilosopher::AbstractPhilosopher(Fork& fork1, Fork& fork2, const unsigned int id) noexcept :
    m_fork1(fork1),
    m_fork2(fork2),
    m_id(id)
{
}

void AbstractPhilosopher::start(const PhilosopherContext& context, std::stop_token stopToken)
{
    auto& [outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist, startLatch] = context;

    startLatch.arrive_and_wait(); // Wait for all philosophers to be ready

    while (!stopToken.stop_requested())
    {
        think(outputMutex, { randomMutex, randomGenerator, thinkingTimeDist });
        if (stopToken.stop_requested())
        {
            return; // Don't attempt to eat if stop requested after thinking
        }
        eat(outputMutex, { randomMutex, randomGenerator, eatingTimeDist });
    }
}

void AbstractPhilosopher::think(std::mutex& outputMutex, const TimeGenerator& thinkingTimeGenerator)
{
    displayThinking(outputMutex);
    const int thinkingTime = getRandomTime(thinkingTimeGenerator);
    std::this_thread::sleep_for(std::chrono::milliseconds(thinkingTime));
}

int AbstractPhilosopher::getRandomTime(const TimeGenerator& timeGenerator) const
{
    auto& [randomMutex, randomGenerator, timeDist] = timeGenerator;
    std::lock_guard<std::mutex> randomLock { randomMutex };
    return timeDist(randomGenerator);
}

void AbstractPhilosopher::displayGrabbedFork(std::mutex& outputMutex, const unsigned int forkId) const
{
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << m_id << " grabbed FORK " << forkId << std::endl;
}

void AbstractPhilosopher::displayLetGoOfFork(std::mutex& outputMutex, const unsigned int forkId) const
{
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << m_id << " let go of FORK " << forkId << std::endl;
}

void AbstractPhilosopher::displayEating(std::mutex& outputMutex) const
{
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << m_id << " EATING" << std::endl;
}

void AbstractPhilosopher::displayThinking(std::mutex& outputMutex) const
{
    std::lock_guard<std::mutex> lock(outputMutex);
    std::cout << "Philosopher " << m_id << " THINKING" << std::endl;
}
