#include "AbstractPhilosopher.h"

#include "Fork.h"

#include <iostream>
#include <thread>

AbstractPhilosopher::AbstractPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept :
    m_leftFork(leftFork),
    m_rightFork(rightFork),
    m_id(id)
{
}

void AbstractPhilosopher::start(const PhilosopherContext& context)
{
    auto& [outputMutex, randomMutex, randomGenerator, thinkingTimeDist, eatingTimeDist] = context;
    while (true)
    {
        think(outputMutex, { randomMutex, randomGenerator, thinkingTimeDist });
        eat(outputMutex, { randomMutex, randomGenerator, eatingTimeDist });
    }
}

void AbstractPhilosopher::think(std::mutex& outputMutex, const TimeGenerator& thinkingTimeGenerator)
{
    displayThinking(outputMutex);
    const int thinkingTime = getRandomTime(thinkingTimeGenerator);
    std::this_thread::sleep_for(std::chrono::milliseconds(thinkingTime));
}

int AbstractPhilosopher::getRandomTime(const TimeGenerator& timeGenerator)
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
