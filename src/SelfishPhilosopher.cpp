#include "SelfishPhilosopher.h"

#include "Fork.h"

#include <chrono>
#include <memory>
#include <mutex>
#include <thread>

SelfishPhilosopher::SelfishPhilosopher(Fork& firstFork, Fork& secondFork, const unsigned int id) noexcept :
    AbstractPhilosopher(firstFork, secondFork, id)
{
}

SelfishPhilosopher::~SelfishPhilosopher() = default;

void SelfishPhilosopher::eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator)
{
    std::unique_lock<Fork> firstForkLock(m_fork1);
    displayGrabbedFork(outputMutex, m_fork1.getId());

    std::unique_lock<Fork> secondForkLock(m_fork2);
    displayGrabbedFork(outputMutex, m_fork2.getId());

    displayEating(outputMutex);

    const int eatingTime = getRandomTime(eatingTimeGenerator);
    std::this_thread::sleep_for(std::chrono::milliseconds(eatingTime));

    firstForkLock.unlock();
    displayLetGoOfFork(outputMutex, m_fork1.getId());

    secondForkLock.unlock();
    displayLetGoOfFork(outputMutex, m_fork2.getId());
}
