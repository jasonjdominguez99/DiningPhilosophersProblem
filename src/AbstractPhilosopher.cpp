#include "AbstractPhilosopher.h"

#include "Fork.h"

#include <iostream>
#include <thread>

AbstractPhilosopher::AbstractPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) :
    m_leftFork(leftFork),
    m_rightFork(rightFork),
    m_id(id)
{
}

void AbstractPhilosopher::start(std::mutex&                      outputMutex,
                                std::mutex&                      randomMutex,
                                std::mt19937&                    randomGenerator,
                                std::uniform_int_distribution<>& thinkingTimeDist,
                                std::uniform_int_distribution<>& eatingTimeDist)
{
    while (true)
    {
        think(outputMutex, randomMutex, randomGenerator, thinkingTimeDist);
        eat(outputMutex, randomMutex, randomGenerator, eatingTimeDist);
    }
}

void AbstractPhilosopher::think(std::mutex&                      outputMutex,
                                std::mutex&                      randomMutex,
                                std::mt19937&                    randomGenerator,
                                std::uniform_int_distribution<>& thinkingTimeDist)
{
    {
        std::lock_guard<std::mutex> lock(outputMutex);
        std::cout << "Philosopher " << m_id << " THINKING" << std::endl;
    }

    std::unique_lock<std::mutex> randomLock { randomMutex };
    const int                    sleepingTime = thinkingTimeDist(randomGenerator);
    randomLock.unlock();

    std::this_thread::sleep_for(std::chrono::milliseconds(sleepingTime));
}
