#include "SelfishPhilosopher.h"
#include "Fork.h"

#include <iostream>
#include <mutex>
#include <thread>

SelfishPhilosopher::SelfishPhilosopher(Fork& leftFork, Fork& rightFork, const unsigned int id) noexcept :
    AbstractPhilosopher(leftFork, rightFork, id)
{
}

void SelfishPhilosopher::eat(std::mutex& outputMutex, const TimeGenerator& eatingTimeGenerator)
{
    std::unique_lock<Fork> leftForkLock(m_leftFork);
    displayGrabbedFork(outputMutex, m_leftFork.getId());

    std::unique_lock<Fork> rightForkLock(m_rightFork);
    displayGrabbedFork(outputMutex, m_rightFork.getId());

    displayEating(outputMutex);

    const int eatingTime = getRandomTime(eatingTimeGenerator);
    std::this_thread::sleep_for(std::chrono::milliseconds(eatingTime));

    leftForkLock.unlock();
    displayLetGoOfFork(outputMutex, m_leftFork.getId());

    rightForkLock.unlock();
    displayLetGoOfFork(outputMutex, m_rightFork.getId());
}
